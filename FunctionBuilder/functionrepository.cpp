#include "functionrepository.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>

#include <algorithm>
#include <utility>

void FunctionRepository::addFunction(GraphFunction function)
{
    functions.push_back(std::move(function));
}

void FunctionRepository::deleteFunctionById(int id)
{
    auto it = functions.end();
    for (auto current = functions.begin(); current != functions.end(); ++current) {
        if (current->getId() == id) {
            it = current;
            break;
        }
    }
    if (it != functions.end()) {
        functions.erase(it);
    }
}

GraphFunction* FunctionRepository::getFunctionById(int id)
{
    for (auto& function : functions) {
        if (function.getId() == id) {
            return &function;
        }
    }
    return nullptr;
}

void FunctionRepository::moveFunction(int oldIndex, int newIndex)
{
    const int count = functions.size();
    if (oldIndex < 0 || newIndex < 0 || oldIndex >= count || newIndex >= count || oldIndex == newIndex) {
        return;
    }
    auto first = functions.begin();
    if (oldIndex < newIndex) {
        std::rotate(first + oldIndex, first + oldIndex + 1, first + newIndex + 1);
    }
    else {
        std::rotate(first + newIndex, first + oldIndex, first + oldIndex + 1);
    }
}

bool FunctionRepository::saveFile(const QString& fileName, QString& error) const
{
    QJsonArray array;
    for (const auto& function : functions) {
        QJsonArray params;
        for (const auto& [name, p] : function.getParameters()) {
            params.append(QJsonObject{{"name", QString(QChar::fromLatin1(name))},
                                      {"minimum", p.minimum}, {"maximum", p.maximum},
                                      {"value", p.value}});
        }
        array.append(QJsonObject{{"expression", function.getExpression()},
                                 {"color", function.getColor().name(QColor::HexArgb)},
                                 {"isVisible", function.isVisible()}, {"parameters", params}});
    }
    const QByteArray bytes = QJsonDocument(QJsonObject{{"version", 1}, {"functions", array}})
                                 .toJson(QJsonDocument::Indented);
    QSaveFile file(fileName);
    if (!file.open(QIODevice::WriteOnly) || file.write(bytes) != bytes.size() || !file.commit()) {
        error = file.errorString();
        return false;
    }
    return true;
}

static QString readFunction(const QJsonObject& obj, int id, std::vector<GraphFunction>& result)
{
    if (!obj["expression"].isString() || !obj["isVisible"].isBool()
        || !obj["color"].isString() || !obj["parameters"].isArray())
        return QStringLiteral("Проверьте поля expression, color, isVisible и parameters.");

    const QColor color(obj["color"].toString());
    if (!color.isValid())
        return QStringLiteral("Некорректный цвет.");

    GraphFunction function(id, obj["expression"].toString(), color, obj["isVisible"].toBool());
    auto remaining = function.getParameters();
    const auto array = obj["parameters"].toArray();
    for (const auto& item : array) {
        const auto parameter = item.toObject();
        const QString name = parameter["name"].toString();
        if (name.size() != 1 || !remaining.erase(name.front().toLatin1()))
            return QStringLiteral("Лишний или повторяющийся параметр «%1».").arg(name);
        if (!parameter["minimum"].isDouble() || !parameter["maximum"].isDouble() || !parameter["value"].isDouble() || !function.setParameter(name.front().toLatin1(),
                                      {parameter["minimum"].toDouble(), parameter["maximum"].toDouble(),
                                       parameter["value"].toDouble()}))
            return QStringLiteral("Проверьте диапазон и значение параметра «%1».").arg(name);
    }
    if (!remaining.empty())
        return QStringLiteral("Отсутствует значение параметра «%1».")
                .arg(QChar::fromLatin1(remaining.begin()->first));
    result.push_back(std::move(function));
    return {};
}

bool FunctionRepository::loadFile(const QString& fileName, QString& error)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        error = file.errorString();
        return false;
    }
    const QByteArray bytes = file.readAll();
    if (file.error() != QFileDevice::NoError) {
        error = file.errorString();
        return false;
    }
    QJsonParseError parseError;
    const auto document = QJsonDocument::fromJson(bytes, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        error = QStringLiteral("Ошибка JSON (байт %1). %2")
                    .arg(parseError.offset).arg(parseError.errorString());
        return false;
    }
    const auto root = document.object();
    if (root["version"].toDouble() != 1.0 || !root["functions"].isArray()) {
        error = QStringLiteral("Ожидается файл версии 1 с массивом functions.");
        return false;
    }
    std::vector<GraphFunction> loaded;
    const auto array = root["functions"].toArray();
    for (const auto& entry : array) {
        int id = static_cast<int>(loaded.size());
        const auto problem = readFunction(entry.toObject(), id, loaded);
        if (!problem.isEmpty()) {
            error = QStringLiteral("Карточка %1. %2").arg(id + 1).arg(problem);
            return false;
        }
    }
    functions.swap(loaded);
    return true;
}

void FunctionRepository::setTime(double t) {
    for (auto& f : functions) {
        f.setTime(t);
    }
}

bool FunctionRepository::hasTimeDependentFunctions() const {
    return std::any_of(functions.begin(), functions.end(), [](const GraphFunction& f) {return f.isVisible() && f.isValid() && f.usesTime(); });
}
