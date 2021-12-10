#include <QApplication>
#include "game.hpp"
#include "shotgungoose.hpp"
#include "snipergoose.hpp"
#include "poopergoose.hpp"
#include "mamagoose.hpp"

int main(int argc, char *argv[])
{
    QList<QPointF> path;
    path << QPoint(0,0) << QPoint(400, 400);
    QList<QList<QPointF>> paths;
    paths << path;
    QApplication a(argc, argv);
    Game* game = new Game(paths);
	
	game->show();
	// Build a ShotgunGoose
	ShotgunGoose* shotgunGoose = new ShotgunGoose(game->GetScene());
	game->SetBuild(shotgunGoose);
	QMouseEvent eve1((QEvent::MouseMove), QPoint(100,100), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
	game->mousePressEvent(&eve1);

	// Build a SniperGoose
	SniperGoose* sniperGoose = new SniperGoose(game->GetScene());
	game->SetBuild(sniperGoose);
	QMouseEvent eve2((QEvent::MouseMove), QPoint(150,150), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
	game->mousePressEvent(&eve2);


	game->ClearTowers();


	// Build a poopergoose
	PooperGoose* pooperGoose = new PooperGoose(game->GetScene());
	game->SetBuild(pooperGoose);
	QMouseEvent eve3((QEvent::MouseMove), QPoint(100,100), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
	game->mousePressEvent(&eve3);

	// Build a mamagoose
	MamaGoose* mamaGoose = new MamaGoose(game->GetScene());
	game->SetBuild(mamaGoose);
	QMouseEvent eve4((QEvent::MouseMove), QPoint(150,150), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
	game->mousePressEvent(&eve4);

	game->StartWave();
	game->close();
	return 0;
}
