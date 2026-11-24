#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_settingsdialog.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QSlider>
#include <QToolButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphCanvas->setRepository(&repository);
    ui->functionsLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    connect(ui->deleteButton, &QToolButton::clicked, this, [this] {
        const int lastRow = ui->functionsLayout->count() - 2;
        if (lastRow >= 0)
            removeFunctionRow(ui->functionsLayout->itemAt(lastRow)->widget());
    });
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::showSettings);

    connect(ui->addButton, &QAbstractButton::clicked, this, &MainWindow::addFunctionRow);
    connect(ui->actionResetScale, &QAction::triggered, ui->graphCanvas, &GraphCanvas::resetView);
    connect(ui->graphCanvas, &GraphCanvas::cursorPositionChanged, this, [this](double x, double y) {
        statusBar()->showMessage(QString("X: %1 | Y: %2").arg(x, 0, 'f', 2).arg(y, 0, 'f', 2));
    });
    connect(ui->actionAddFunction, &QAction::triggered, this, &MainWindow::addFunctionRow);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    int totalWidth = ui->centralwidget->width();
    ui->functionPanel->setMinimumWidth(static_cast<int>(totalWidth*0.30));
    ui->functionPanel->setMaximumWidth(static_cast<int>(totalWidth*0.30));
}

void MainWindow::addFunctionRow() {
    int id = nextFunctionId++;

    const QStringList colors = {
        "#A635D5", "#F03E51", "#327DFA", "#32CF56"
    };


    QColor initialColor(colors[id % colors.size()]);

    repository.addFunction(GraphFunction(id, "", initialColor, true));
    createFunctionRow(id);
}

void MainWindow::createFunctionRow(int id)
{
    auto* function = repository.getFunctionById(id);
    QFrame *row = new QFrame(ui->scrollAreaWidgetContents);
    row->setObjectName("functionRow");
    row->setProperty("functionId", id);
    row->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    auto* card = new QVBoxLayout(row);
    card->setContentsMargins(10, 8, 10, 8);
    card->setSpacing(5);
    auto* layout = new QHBoxLayout;
    layout->setSpacing(6);
    card->addLayout(layout);
    auto* sliders = new QVBoxLayout;
    sliders->setSpacing(5);
    card->addLayout(sliders);

    QToolButton *dragHandle = new QToolButton(row);
    dragHandle->setObjectName("functionDrag");
    dragHandle->setFixedSize(18, 30);
    dragHandle->setCursor(Qt::OpenHandCursor);
    dragHandle->setToolTip("Изменить порядок функции");
    QPixmap gripPixmap(18, 24);
    gripPixmap.fill(Qt::transparent);

    {
        QPainter painter(&gripPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#9CA5B2"));

        for (int y = 6; y <= 18; y += 6) {
            for (int x = 5; x <= 12; x += 7) {
                painter.drawEllipse(QPointF(x, y), 1.7, 1.7);
            }
        }
    }

    dragHandle->setIcon(QIcon(gripPixmap));
    dragHandle->setIconSize(QSize(18, 24));

    dragHandle->installEventFilter(this);

    QToolButton *visibleCheck = new QToolButton(row);
    visibleCheck->setObjectName("functionVisibility");
    visibleCheck->setFixedSize(26, 26);
    visibleCheck->setCheckable(true);
    visibleCheck->setChecked(function->isVisible());
    visibleCheck->setText(function->isVisible() ? "✓" : "");
    visibleCheck->setToolTip("Видимость функции");

    connect(visibleCheck, &QToolButton::toggled,
            row, [this, id, visibleCheck](bool checked) {
                visibleCheck->setText(checked ? "✓" : "");
                if (auto* f = repository.getFunctionById(id))
                    f->setVisibility(checked);

                ui->graphCanvas->requestRedraw();
            });

    QToolButton *colorButton = new QToolButton(row);
    colorButton->setObjectName("functionColor");
    colorButton->setFixedSize(32, 32);
    colorButton->setToolTip("Выбрать цвет функции");

    auto applyColor = [colorButton](const QColor &color) {
        colorButton->setStyleSheet(
            QString(
                "QToolButton {"
                "background-color: %1;"
                "border: none;"
                "border-radius: 6px;"
                "}"
                ).arg(color.name(QColor::HexArgb))
            );
    };

    applyColor(function->getColor());

    connect(colorButton, &QToolButton::clicked,
            row, [this, id, row, applyColor]() {
                auto* current = repository.getFunctionById(id);
                if (!current)
                    return;
                QColor selected = QColorDialog::getColor(
                    current->getColor(), row, "Выбор цвета функции", QColorDialog::ShowAlphaChannel
                    );

                if (!selected.isValid())
                    return;

                applyColor(selected);
                if (auto* f = repository.getFunctionById(id))
                    f->setColor(selected);
                ui->graphCanvas->requestRedraw();
            });

    QLineEdit *expressionEdit = new QLineEdit(row);
    expressionEdit->setObjectName("functionExpression");
    expressionEdit->setPlaceholderText("Введите выражение");
    expressionEdit->setFixedHeight(42);
    expressionEdit->setMinimumWidth(0);

    expressionEdit->setText(function->getExpression());
    expressionEdit->setToolTip(function->getError());
    rebuildSliders(id, sliders);
    connect(expressionEdit, &QLineEdit::textChanged, row,
            [this, id, sliders, expressionEdit](const QString& text) {
                auto* f = repository.getFunctionById(id);
                if (!f)
                    return;
                f->setExpression(text);
                expressionEdit->setToolTip(f->getError());
                rebuildSliders(id, sliders);
                ui->graphCanvas->requestRedraw();
            });

    QToolButton *removeButton = new QToolButton(row);
    removeButton->setObjectName("functionRemove");
    removeButton->setText("×");
    removeButton->setFixedSize(28, 32);
    removeButton->setToolTip("Удалить функцию");

    connect(removeButton, &QToolButton::clicked, row, [this, row] { removeFunctionRow(row); });

    layout->addWidget(dragHandle);
    layout->addWidget(visibleCheck);
    layout->addWidget(colorButton);
    layout->addWidget(expressionEdit, 1);
    layout->addWidget(removeButton);

    ui->functionsLayout->insertWidget(ui->functionsLayout->count() - 1, row);
    ui->deleteButton->setEnabled(true);
}

void MainWindow::removeFunctionRow(QWidget* row)
{
    repository.deleteFunctionById(row->property("functionId").toInt());
    ui->functionsLayout->removeWidget(row);
    ui->deleteButton->setEnabled(ui->functionsLayout->count() > 1);
    row->hide();
    row->deleteLater();
    ui->graphCanvas->requestRedraw();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    auto *handle = qobject_cast<QToolButton *>(watched);

    if (!handle || handle->objectName() != "functionDrag") {
        return QMainWindow::eventFilter(watched, event);
    }

    if (event->type() == QEvent::MouseButtonPress) {
        auto *mouse = static_cast<QMouseEvent *>(event);

        if (mouse->button() == Qt::LeftButton) {
            draggedRow = handle->parentWidget();
            handle->setCursor(Qt::ClosedHandCursor);
            return true;
        }
    }

    if (event->type() == QEvent::MouseMove &&
        draggedRow == handle->parentWidget()) {

        auto *mouse = static_cast<QMouseEvent *>(event);

        if (!(mouse->buttons() & Qt::LeftButton))
            return true;

        auto *layout = ui->functionsLayout;

        QPoint pos = ui->scrollAreaWidgetContents->mapFromGlobal(
            mouse->globalPosition().toPoint()
            );

        QWidget *row = draggedRow.data();

        int newIndex = 0;

        for (int i = 0; i < layout->count(); ++i) {
            QWidget *widget = layout->itemAt(i)->widget();

            if (!widget || widget == row)
                continue;

            if (pos.y() > widget->geometry().center().y())
                ++newIndex;
        }

        int oldIndex = layout->indexOf(row);

        if (oldIndex >= 0 && oldIndex != newIndex) {
            repository.moveFunction(oldIndex, newIndex);
            layout->removeWidget(row);
            layout->insertWidget(newIndex, row);
            ui->graphCanvas->requestRedraw();
        }

        return true;
    }

    if (event->type() == QEvent::MouseButtonRelease) {
        auto *mouse = static_cast<QMouseEvent *>(event);

        if (mouse->button() == Qt::LeftButton &&
            draggedRow == handle->parentWidget()) {

            draggedRow = nullptr;
            handle->setCursor(Qt::OpenHandCursor);
            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::rebuildSliders(int id, QVBoxLayout* layout)
{
    while (auto* item = layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    auto* function = repository.getFunctionById(id);
    for (const auto& [key, parameter] : function->getParameters()) {
        const char name = key;
        auto* strip = new QWidget(layout->parentWidget());
        auto* line = new QHBoxLayout(strip);
        line->setContentsMargins(0, 0, 0, 0);
        line->setSpacing(6);
        const QString letter(QChar::fromLatin1(name));
        auto* valueLabel = new QLabel(strip);
        const auto showValue = [valueLabel, letter](double value) {
            valueLabel->setText(QString("%1 = %2").arg(letter, QString::number(value, 'g', 6)));
            valueLabel->setToolTip(QString::number(value, 'g', 17));
        };
        showValue(parameter.value);

        auto* slider = new QSlider(Qt::Horizontal, strip);
        slider->setObjectName("slider_" + letter);
        slider->setAccessibleName(tr("Параметр %1").arg(letter));
        constexpr int steps = 2000;
        slider->setRange(0, steps);
        const double lo = parameter.minimum;
        const double hi = parameter.maximum;
        slider->setValue(qRound((parameter.value - lo) / (hi - lo) * steps));
        connect(slider, &QSlider::valueChanged, strip, [this, id, name, lo, hi, showValue](int tick) {
            auto* f = repository.getFunctionById(id);
            const double value = tick == steps ? hi : lo + (double(tick) / steps) * (hi - lo);
            if (f && f->setParameterValue(name, value)) {
                showValue(value);
                ui->graphCanvas->requestRedraw();
            }
        });

        line->addWidget(valueLabel);
        line->addWidget(new QLabel(QString::number(lo, 'g', 5), strip));
        line->addWidget(slider, 1);
        line->addWidget(new QLabel(QString::number(hi, 'g', 5), strip));
        layout->addWidget(strip);
    }
}

void MainWindow::showSettings()
{
    QDialog dialog(this);
    Ui::SettingsDialog form;
    form.setupUi(&dialog);
    const QString filter = tr("Файлы JSON (*.json)");
    connect(form.saveButton, &QPushButton::clicked, &dialog, [this, &dialog, filter] {
        QFileDialog picker(&dialog, tr("Сохранить графики"), QString(), filter);
        picker.setAcceptMode(QFileDialog::AcceptSave);
        picker.setDefaultSuffix("json");
        picker.selectFile("functions.json");
        if (picker.exec() != QDialog::Accepted)
            return;
        QString error;
        if (!repository.saveFile(picker.selectedFiles().first(), error)) {
            QMessageBox::warning(&dialog, tr("Ошибка сохранения"), error);
            return;
        }
        dialog.accept();
    });
    connect(form.loadButton, &QPushButton::clicked, &dialog, [this, &dialog, filter] {
        const QString path = QFileDialog::getOpenFileName(&dialog, tr("Загрузить графики"), {}, filter);
        if (path.isEmpty())
            return;
        QString error;
        if (!repository.loadFile(path, error)) {
            QMessageBox::warning(&dialog, tr("Ошибка загрузки"), error);
            return;
        }

        // The spacer is always the last item.
        while (ui->functionsLayout->count() > 1) {
            auto* item = ui->functionsLayout->takeAt(0);
            delete item->widget();
            delete item;
        }
        ui->deleteButton->setEnabled(false);
        ui->graphCanvas->clearSelection();
        for (const auto& f : repository.getRepository())
            createFunctionRow(f.getId());
        nextFunctionId = static_cast<int>(repository.getRepository().size());
        ui->graphCanvas->requestRedraw();
        dialog.accept();
    });
    dialog.exec();
}
