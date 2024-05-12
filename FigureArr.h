#ifndef FIGUREARR_H
#define FIGUREARR_H
#include "FigureBase.h"
#include "FigureColor.h"
#include "FigureType.h"
#include <array>
#include <tuple>
#include <QObject>
#include <QDebug>
#include <array>
#include <utility>
#include <string>
#include <QUrl>
#include <QString>
#include "iostream"



class FigureArr : public QObject
{
    Q_OBJECT

public:
    explicit FigureArr() {
        addFigureToArray(FigureColor::white);
        addFigureToArray(FigureColor::black);
    }
signals:
    void figureMoved(int x, int y);
public slots:
    QString callImage(const int x, const int y){
        auto it = std::find_if(figures.begin(), figures.end(), [&](const FigureBase& figure_base) {
            return figure_base.position.first == x && figure_base.position.second == y;
        });
        if (it != figures.end()) {
            return it->image_path;
        } else {
            return QString(); // or return a default image path
        }
    }
    QUrl convertToQUrl(const QString& imagePath) {
        QUrl url = QUrl::fromLocalFile(imagePath);
        return url;
    }
    // void moveTo(const int x, const int y){
    //     auto it = std::find_if(figures.begin(), figures.end(), [&](const FigureBase& figure_base) {
    //         return figure_base.position.first == x && figure_base.position.second == y;
    //     });
    //     if (it != figures.end()) {
    //         it->position.second += 1;
    //         emit figureMoved(x, y);
    //     }
    // }
private:

    void addFigureToArray(FigureColor color) {
        QString strColor = static_cast<int>(color) ? "black" : "white";
        int colorPosititon = static_cast<int>(color) ? 0 : 48;
        const QString pawnImage = "images/" + strColor + "_pawn.png";
        const QString castleImage = "images/" + strColor + "_castle.png";
        const QString knightImage = "images/" + strColor + "_knight.png";
        const QString bishopImage = "images/" + strColor + "_bishop.png";
        const QString queenImage = "images/" + strColor + "_queen.png";
        const QString kingImage = "images/" + strColor + "_king.png";

        const int pawnRow = color ? 1 : 6;
        const int backRow = color ? 0 : 7;
        for(size_t i{0}; i < 8; ++i){
            std::pair<int, int> position(i, pawnRow);
            figures[colorPosititon + i] = createFigure(FigureType::Pawn, pawnImage, position, false, color);
        }

        figures[colorPosititon + 8] = createFigure(FigureType::Castle, castleImage, std::make_pair(0, backRow), false, color);
        figures[colorPosititon + 9] = createFigure(FigureType::Castle, castleImage, std::make_pair(7, backRow), false, color);
        figures[colorPosititon + 10] = createFigure(FigureType::Knight, knightImage, std::make_pair(1, backRow), false, color);
        figures[colorPosititon + 11] = createFigure(FigureType::Knight, knightImage, std::make_pair(6, backRow), false, color);
        figures[colorPosititon + 12] = createFigure(FigureType::Bishop, bishopImage, std::make_pair(2, backRow), false, color);
        figures[colorPosititon + 13] = createFigure(FigureType::Bishop, bishopImage, std::make_pair(5, backRow), false, color);
        figures[colorPosititon + 14] = createFigure(FigureType::King,   kingImage,   std::make_pair(4, backRow), false, color);
        figures[colorPosititon + 15] = createFigure(FigureType::Queen,  queenImage,  std::make_pair(3, backRow), false, color);
    }
    FigureBase createFigure(FigureType type, QString image_path, std::pair<int, int> position, bool is_killed, FigureColor color){
        return FigureBase(type, image_path, position, is_killed, color);
    }
    static const int size{64};
public:
    FigureColor color;
    std::array<FigureBase, size> figures;
};

#endif // FIGUREARR_H
