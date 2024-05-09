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
    void pieceMoved(int x, int y);
public slots:
     QString callMeImage(const int x, const int y){
        auto it = std::find_if(pieces.begin(), pieces.end(), [&](const FigureBase& figure_base) {
            return figure_base.position.first == x && figure_base.position.second == y;
        });
        if (it != pieces.end()) {
            return it->image_path;
        } else {
            return QString(); // or return a default image path
        }
    }
    QUrl convertToQUrl(const QString& imagePath) {
        QUrl url = QUrl::fromLocalFile(imagePath);
        return url;
    }
    void moveTo(const int x, const int y){
        auto it = std::find_if(pieces.begin(), pieces.end(), [&](const FigureBase& figure_base) {
            return figure_base.position.first == x && figure_base.position.second == y;
        });
        if (it != pieces.end()) {
            it->position.second += 1;
            emit pieceMoved(x, y);
        }
    }
private:

    void addFigureToArray(FigureColor color) {
        QString strColor = static_cast<int>(color) ? "black" : "white";
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
            pieces.push_back(createPiece(FigureType::Pawn, pawnImage, position, false, color));
        }

        pieces.push_back(createPiece(FigureType::Castle, castleImage, std::make_pair(0, backRow), false, color));
        pieces.push_back(createPiece(FigureType::Castle, castleImage, std::make_pair(7, backRow), false, color));
        pieces.push_back(createPiece(FigureType::Knight, knightImage, std::make_pair(1, backRow), false, color));
        pieces.push_back(createPiece(FigureType::Knight, knightImage, std::make_pair(6, backRow), false, color));
        pieces.push_back(createPiece(FigureType::Bishop, bishopImage, std::make_pair(2, backRow), false, color));
        pieces.push_back(createPiece(FigureType::Bishop, bishopImage, std::make_pair(5, backRow), false, color));
        pieces.push_back(createPiece(FigureType::King,   kingImage,   std::make_pair(4, backRow), false, color));
        pieces.push_back(createPiece(FigureType::Queen,  queenImage,  std::make_pair(3, backRow), false, color));
    }
    FigureBase createPiece(FigureType type, QString image_path, std::pair<int, int> position, bool is_killed, FigureColor color){
        return FigureBase(type, image_path, position, is_killed, color);
    }

public:
    FigureColor color;
    std::vector<FigureBase> pieces;
};

#endif // FIGUREARR_H
