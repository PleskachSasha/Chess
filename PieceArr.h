#ifndef PIECEARR_H
#define PIECEARR_H
#include "Piece.h"
#include "PieceColor.h"
#include "PieceType.h"
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



class PieceArr : public QObject
{
    Q_OBJECT

public:
    explicit PieceArr(PieceColor color) {
        createArray(color);
    }
signals:
public slots:
    void callMe(){
        qDebug() << "debug" << "debug";}


    QString callMeImage(const int x, const int y){
        //qDebug() << "x-" << x << "y-" << y << " ";
        auto it = std::find_if(pieces.begin(), pieces.end(), [&](const Piece& piece) {
            return piece.position.first == x && piece.position.second == y;
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
private:

    void createArray(PieceColor color) {
        QString strColor = static_cast<int>(color) ? "black" : "white";
        const QString pawnImage = strColor + "_pawn.png";
        const QString castleImage = strColor + "_castle.png";
        const QString knightImage = strColor + "_knight.png";
        const QString bishopImage = strColor + "_bishop.png";
        const QString queenImage = strColor + "_queen.png";
        const QString kingImage = strColor + "_king.png";

        const int pawnRow = color ? 1 : 6;
        const int backRow = color ? 0 : 7;

        for(size_t i{0}; i < 8; ++i){
            std::pair<int, int> position(i, pawnRow);
            pieces[i] = createPiece(PieceType::Pawn, pawnImage, position, false, color);
        }

        pieces[8]  = createPiece(PieceType::Castle, castleImage, std::make_pair(0, backRow), false, color);
        pieces[9]  = createPiece(PieceType::Castle, castleImage, std::make_pair(7, backRow), false, color);
        pieces[10] = createPiece(PieceType::Knight, knightImage, std::make_pair(1, backRow), false, color);
        pieces[11] = createPiece(PieceType::Knight, knightImage, std::make_pair(6, backRow), false, color);
        pieces[12] = createPiece(PieceType::Bishop, bishopImage, std::make_pair(2, backRow), false, color);
        pieces[13] = createPiece(PieceType::Bishop, bishopImage, std::make_pair(5, backRow), false, color);
        pieces[14] = createPiece(PieceType::King,   kingImage,   std::make_pair(4, backRow), false, color);
        pieces[15] = createPiece(PieceType::Queen,  queenImage,  std::make_pair(3, backRow), false, color);
    }
    Piece createPiece(PieceType type, QString image_path, std::pair<int, int> position, bool is_killed, PieceColor color){
        return Piece(type, image_path, position, is_killed, color);
    }


    static constexpr int size{16};

public:
    PieceColor color;
    std::array<Piece, size> pieces;
};

#endif // PIECEARR_H
