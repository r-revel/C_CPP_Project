#include "./figure.h"
#include <algorithm>
#include <cmath>

namespace geometry {

constexpr size_t INITIAL_CAPACITY = 4;  // Начальная емкость массива вершин

Figure::Figure() : vertices_(new Point[INITIAL_CAPACITY]), capacity_(INITIAL_CAPACITY), vertexCount_(0) {}

Figure::Figure(const Point& vertex) : Figure() {
    addVertex(vertex);
}

Figure::Figure(size_t count, const Point* vertices) : Figure() {
    if (count == 0) {
        throw std::invalid_argument("Количество вершин не может быть нулевым");
    }
    for (size_t i = 0; i < count; ++i) {
        addVertex(vertices[i]);
    }
}

Figure::Figure(const Figure& other) 
    : vertices_(new Point[other.capacity_]), 
      capacity_(other.capacity_), 
      vertexCount_(other.vertexCount_) {
    std::copy(other.vertices_, other.vertices_ + vertexCount_, vertices_);
}

Figure::Figure(Figure&& other) noexcept
    : vertices_(other.vertices_),
      capacity_(other.capacity_),
      vertexCount_(other.vertexCount_) {
    other.vertices_ = nullptr;
    other.capacity_ = 0;
    other.vertexCount_ = 0;
}

Figure::~Figure() {
    delete[] vertices_;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        Point* newVertices = new Point[other.capacity_];
        std::copy(other.vertices_, other.vertices_ + other.vertexCount_, newVertices);
        
        delete[] vertices_;
        vertices_ = newVertices;
        capacity_ = other.capacity_;
        vertexCount_ = other.vertexCount_;
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        delete[] vertices_;
        
        vertices_ = other.vertices_;
        capacity_ = other.capacity_;
        vertexCount_ = other.vertexCount_;
        
        other.vertices_ = nullptr;
        other.capacity_ = 0;
        other.vertexCount_ = 0;
    }
    return *this;
}

void Figure::resize(size_t newCapacity) {
    if (newCapacity <= capacity_) return;
    
    Point* newVertices = new Point[newCapacity];
    std::copy(vertices_, vertices_ + vertexCount_, newVertices);
    
    delete[] vertices_;
    vertices_ = newVertices;
    capacity_ = newCapacity;
}

void Figure::addVertex(const Point& vertex) {
    if (vertexCount_ == capacity_) {
        resize(capacity_ * 2);
    }
    vertices_[vertexCount_++] = vertex;
}

Point& Figure::operator[](size_t index) {
    if (index >= vertexCount_) {
        throw std::out_of_range("Индекс вершины вне допустимого диапазона");
    }
    return vertices_[index];
}

const Point& Figure::operator[](size_t index) const {
    if (index >= vertexCount_) {
        throw std::out_of_range("Индекс вершины вне допустимого диапазона");
    }
    return vertices_[index];
}

Figure& Figure::operator+=(const Point& vertex) {
    addVertex(vertex);
    return *this;
}

void Figure::rotate(const Point& center, int angleDegrees) {
    if (angleDegrees % 90 != 0) {
        throw std::invalid_argument("Угол должен быть кратным 90 градусам");
    }
    
    // Нормализация угла в диапазон 0-360 градусов
    angleDegrees = angleDegrees % 360;
    if (angleDegrees < 0) angleDegrees += 360;
    
    // Количество поворотов на 90 градусов
    const int rotations = angleDegrees / 90;
    
    for (size_t i = 0; i < vertexCount_; ++i) {
        // Перенос в начало координат
        Point translated = vertices_[i] - center;
        
        // Применение поворотов
        for (int r = 0; r < rotations; ++r) {
            // Поворот на 90 градусов против часовой стрелки
            double newX = -translated.getY();
            double newY = translated.getX();
            translated = Point(newX, newY);
        }
        
        // Обратный перенос
        vertices_[i] = translated + center;
    }
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    size_t count;
    is >> count;
    
    if (count == 0) {
        throw std::invalid_argument("Количество вершин не может быть нулевым");
    }
    
    figure = Figure();
    
    for (size_t i = 0; i < count; ++i) {
        Point vertex;
        is >> vertex;
        figure.addVertex(vertex);
    }
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    os << "Фигура с " << figure.vertexCount_ << " вершинами: ";
    for (size_t i = 0; i < figure.vertexCount_; ++i) {
        os << figure.vertices_[i];
        if (i < figure.vertexCount_ - 1) {
            os << ", ";
        }
    }
    return os;
}

}