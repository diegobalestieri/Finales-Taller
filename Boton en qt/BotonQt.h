//
// Created by diego on 17/2/20.
//

#ifndef SDLDIBUJAR_BOTONQT_H
#define SDLDIBUJAR_BOTONQT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>

class BotonQt : public QWidget {
private:
    QPushButton boton;
    QLineEdit entrada;

public:
    explicit BotonQt(QWidget* parent = 0);

    void saludar();
};


#endif //SDLDIBUJAR_BOTONQT_H
