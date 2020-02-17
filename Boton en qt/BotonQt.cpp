//
// Created by diego on 17/2/20.
//

#include <iostream>
#include "BotonQt.h"

BotonQt::BotonQt(QWidget* parent) : boton("Saludar", this), entrada(this) {
    this->setGeometry(500,500,500,500);
    boton.setGeometry(200, 200, 100, 50);
    entrada.setGeometry(200, 100, 200, 50);
    QObject::connect(&boton, &QPushButton::clicked, this, &BotonQt::saludar);
}

void BotonQt::saludar() {
    std::cout<<"Hola "<<entrada.text().toStdString()<<'\n';
    QWidget::close();
}
