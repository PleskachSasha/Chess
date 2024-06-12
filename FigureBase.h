#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "FigureType.h"
#include "FigureColor.h"
#include <tuple>
#include <string>
#include <QString>
#include <QDebug>

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

    friend QDebug operator<<(QDebug dbg, const FigureBase &figure) {
        dbg.nospace() << "FigureBase(type: " << static_cast<int>(figure.type)
                      << ", image_path: " << figure.image_path
                      << ", position: (" << figure.position.first << ", " << figure.position.second << ")"
                      << ", is_killed: " << figure.is_killed
                      << ", color: " << static_cast<int>(figure.color) << ")";
        return dbg.space();
    }
};

#endif // FIGUREBASE_H
