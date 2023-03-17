#include "laborator10.h"
#include "gui.h"
#include "teste.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRepo repo{ "activitati.txt" };
    Validator val;
    Repo wishlist;
    Service srv{ val,repo,wishlist };
    EventsGUI gui{ srv };
    teste test;
    test.run_tests();
    gui.show();
    return a.exec();
}
