//
// Created by мвидео on 30.11.2021.
//

#ifndef DECORATOR_DECORATOR_H
#define DECORATOR_DECORATOR_H

#include <iostream>
#include <string>

/* Что реализуем? Предположим, что мы пишем утилиту для
 * создания и наложения шейдеров для нашего игрового движка.
 * В самом начале мы имеем какую-то сетку на нашей
 * сцене/поверхности, а поверх неё мы выборочно накладываем
 * цвета и какие-то текстуры - реализуем данный функционал
 * с помощью паттерна "Decorator". */

/*** ИНТЕРФЕЙС СЕТКИ - АБСТРАКТНАЯ СЕТКА ***/
class IMesh {
public:
    virtual ~IMesh() = default;
    virtual std::string addMeshProperties() = 0;
};

/*** БАЗОВАЯ СЕТКА - ОНА БУДЕТ ДЕКОРИРОВАТЬСЯ ЦВЕТАМИ И ТЕКСТУРАМИ ***/
class RegularMesh : public IMesh {
public:
    ~RegularMesh() override = default;
    std::string addMeshProperties() override {
        return "Basic Mesh. No texture";
    }
};

/*** АБСТРАКТНЫЙ ИЛИ БАЗОВЫЙ ДЕКОРАТОР ***/
class Decorator : public IMesh {
protected:
    IMesh* mesh_;
public:
    Decorator(IMesh* mesh) : mesh_(mesh) {}
    ~Decorator() override { delete mesh_; }
    virtual std::string decoratorProperties(std::string decoration) = 0;
    std::string addMeshProperties() override {
        /* Делегируем работу обёрнутому компоненту */
        return this->mesh_->addMeshProperties();
    }
};

/*** КОНКРЕТНЫЕ ДЕКОРАТОРЫ - ТО, ЧТО МЫ МОЖЕМ НАЛОЖИТЬ НА СЕТКУ ***/
class Texture : public Decorator {
private:
    std::string texture_;
public:
    Texture(IMesh* mesh, std::string texture) : Decorator(mesh), texture_(texture) {}
    std::string decoratorProperties(std::string texture) override {
        return texture + " texture was added";
    }
    std::string addMeshProperties() override {
        return this->mesh_->addMeshProperties() + " -> " + decoratorProperties(texture_);
    }
};

class Color : public Decorator {
private:
    std::string color_;
public:
    Color(IMesh* mesh, std::string color) : Decorator(mesh), color_(color) {}
    std::string decoratorProperties(std::string color) override {
        return color + " color was added";
    }
    std::string addMeshProperties() override {
        return this->mesh_->addMeshProperties() + " -> " + decoratorProperties(color_);
    }
};

class Shader : public Decorator {
private:
    std::string shader_;
public:
    Shader(IMesh* mesh, std::string shader) : Decorator(mesh), shader_(shader) {}
    std::string decoratorProperties(std::string shader) override {
        return shader + " shader was added";
    }
    std::string addMeshProperties() override {
        return this->mesh_->addMeshProperties() + " -> " + decoratorProperties(shader_);
    }
};

class Effect : public Decorator {
private:
    std::string effect_;
public:
    Effect(IMesh* mesh, std::string effect) : Decorator(mesh), effect_(effect) {}
    std::string decoratorProperties(std::string effect) override {
        return effect + " effect was added";
    }
    std::string addMeshProperties() override {
        return this->mesh_->addMeshProperties() + " -> " + decoratorProperties(effect_);
    }
};



#endif //DECORATOR_DECORATOR_H
