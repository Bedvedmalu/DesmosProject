#ifndef FUNCTIONREPOSITORY_H
#define FUNCTIONREPOSITORY_H

#include "graphfunction.h"
#include <vector>

class FunctionRepository
{
public:
    void addFunction(GraphFunction function);
    void deleteFunctionById(int id);
    GraphFunction* getFunctionById(int id);
    void moveFunction(int oldIndex, int newIndex);
    std::vector<GraphFunction>& getRepository() { return functions; }

    bool saveFile(const QString& fileName, QString& error) const;
    bool loadFile(const QString& fileName, QString& error);

    void setTime(double t);
    bool hasTimeDependentFunctions() const;
private:
    std::vector<GraphFunction> functions;
};

#endif
