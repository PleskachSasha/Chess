#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "FigureType.h"
#include "FigureColor.h"
#include <tuple>
#include <string>
#include <QString>

class FigureBase{
public:
    FigureBase() {}
    FigureBase(FigureType type, QString image_path, std::pair<int, int> position, bool is_killed, FigureColor color)
        :type(type),  image_path(image_path), position(position), is_killed(is_killed), color(color)
    {}
    QString image_path;
    void move() const;

    FigureType type;
    std::pair<int, int> position;
    bool is_killed;
    FigureColor color;
};

#endif // FIGUREBASE_H
