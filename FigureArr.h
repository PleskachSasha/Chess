#ifndef FIGUREARR_H
#define FIGUREARR_H
#include "FigureBase.h"
#include "FigureColor.h"
#include "FigureType.h"
#include <array>
#include <tuple>
#include <QObject>
#include <QDebug>
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
    void move();

public slots:
    QString callImage(const int x, const int y){
        auto it = std::find_if(figures.begin(), figures.end(), [&](const FigureBase& figure_base) {
            return figure_base.position.first == x && figure_base.position.second == y;
        });
        if (it != figures.end()) {
            return it->image_path;
        } else {
            return QString();
        }
    }

    QUrl convertToQUrl(const QString& imagePath) {
        QUrl url = QUrl::fromLocalFile(imagePath);
        return url;
    }
    Q_INVOKABLE void onMove(const int fromX, const int fromY, const int toX, const int toY) {
        auto it = std::find_if(figures.begin(), figures.end(), [&](const FigureBase& figure_base) {
            return figure_base.position.first == fromX && figure_base.position.second == fromY;
        });
        qDebug() << it->type;
        if (it != figures.end()) {
            it->position.first = toX;
            it->position.second = toY;
            emit move();
        }
    }
    std::vector<std::pair<int, int>> possibleMove(const int x, const int y) {
        auto it = std::find_if(figures.begin(), figures.end(), [&](const FigureBase& figure_base) {
            return figure_base.position.first == x && figure_base.position.second == y;
        });

        if (it == figures.end()) {
            return {}; // No figure at the given position
        }

        FigureType type = it->type;
        FigureColor color = it->color;
        std::vector<std::pair<int, int>> moves;

        switch (type) {
        case Pawn:
            if (color == FigureColor::white) {
                moves.push_back({x, y + 1});
                if (y == 2) { // Initial two-step move for white pawns
                    moves.push_back({x, y + 2});
                }
            } else {
                moves.push_back({x, y - 1});
                if (y == 7) {
                    moves.push_back({x, y - 2});
                }
            }
            break;

        case Bishop:
            for (int i = 1; i < 8; ++i) {
                moves.push_back({x + i, y + i});
                moves.push_back({x + i, y - i});
                moves.push_back({x - i, y + i});
                moves.push_back({x - i, y - i});
            }
            break;

        case Knight:
            moves.push_back({x + 2, y + 1});
            moves.push_back({x + 2, y - 1});
            moves.push_back({x - 2, y + 1});
            moves.push_back({x - 2, y - 1});
            moves.push_back({x + 1, y + 2});
            moves.push_back({x + 1, y - 2});
            moves.push_back({x - 1, y + 2});
            moves.push_back({x - 1, y - 2});
            break;

        case Castle:
            for (int i = 1; i < 8; ++i) {
                moves.push_back({x + i, y});
                moves.push_back({x - i, y});
                moves.push_back({x, y + i});
                moves.push_back({x, y - i});
            }
            break;

        case Queen:
            for (int i = 1; i < 8; ++i) {
                moves.push_back({x + i, y});
                moves.push_back({x - i, y});
                moves.push_back({x, y + i});
                moves.push_back({x, y - i});
                moves.push_back({x + i, y + i});
                moves.push_back({x + i, y - i});
                moves.push_back({x - i, y + i});
                moves.push_back({x - i, y - i});
            }
            break;

        case King:
            moves.push_back({x + 1, y});
            moves.push_back({x - 1, y});
            moves.push_back({x, y + 1});
            moves.push_back({x, y - 1});
            moves.push_back({x + 1, y + 1});
            moves.push_back({x + 1, y - 1});
            moves.push_back({x - 1, y + 1});
            moves.push_back({x - 1, y - 1});
            break;
        }

        moves.erase(std::remove_if(moves.begin(), moves.end(), [](const std::pair<int, int>& move) {
                        return move.first < 1 || move.first > 8 || move.second < 1 || move.second > 8;
                    }), moves.end());


        return moves;
    }

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
            figures.push_back(createFigure(FigureType::Pawn, pawnImage, position, false, color));
        }

        figures.push_back(createFigure(FigureType::Castle, castleImage, std::make_pair(0, backRow), false, color));
        figures.push_back(createFigure(FigureType::Castle, castleImage, std::make_pair(7, backRow), false, color));
        figures.push_back(createFigure(FigureType::Knight, knightImage, std::make_pair(1, backRow), false, color));
        figures.push_back(createFigure(FigureType::Knight, knightImage, std::make_pair(6, backRow), false, color));
        figures.push_back(createFigure(FigureType::Bishop, bishopImage, std::make_pair(2, backRow), false, color));
        figures.push_back(createFigure(FigureType::Bishop, bishopImage, std::make_pair(5, backRow), false, color));
        figures.push_back(createFigure(FigureType::King,   kingImage,   std::make_pair(4, backRow), false, color));
        figures.push_back(createFigure(FigureType::Queen,  queenImage,  std::make_pair(3, backRow), false, color));
    }
    FigureBase createFigure(FigureType type, QString image_path, std::pair<int, int> position, bool is_killed, FigureColor color){
        return FigureBase(type, image_path, position, is_killed, color);
    }
    static const int size{64};
public:
    FigureColor color;
    std::vector<FigureBase> figures;
};
#endif
