
#ifndef GEOMETRY_FIGURE_H
#define GEOMETRY_FIGURE_H

#include "../point/point.h"
#include <iostream>
#include <stdexcept>

namespace geometry
{

  class Figure
  {
  private:
    Point *vertices_;    ///< Динамический массив вершин
    size_t capacity_;    ///< Текущая вместимость массива
    size_t vertexCount_; ///< Текущее количество вершин

    void resize(size_t newCapacity);

  public:
    Figure();

    /**
     * @brief Конструктор с одной вершиной.
     * @param vertex Единственная вершина фигуры
     */
    explicit Figure(const Point &vertex);

    /**
     * @brief Конструктор с массивом вершин.
     * @param count Количество вершин
     * @param vertices Массив вершин
     * @throws std::invalid_argument Если count равен нулю
     */
    Figure(size_t count, const Point *vertices);

    /**
     * @brief Конструктор копирования.
     * @param other Фигура для копирования
     */
    Figure(const Figure &other);

    /**
     * @brief Конструктор перемещения.
     * @param other Фигура для перемещения
     */
    Figure(Figure &&other) noexcept;

    ~Figure();

    /**
     * @brief Оператор присваивания копированием.
     * @param other Фигура для копирования
     * @return Ссылка на эту фигуру
     */
    Figure &operator=(const Figure &other);

    /**
     * @brief Оператор присваивания перемещением.
     * @param other Фигура для перемещения
     * @return Ссылка на эту фигуру
     */
    Figure &operator=(Figure &&other) noexcept;

    /**
     * @brief Получает количество вершин.
     * @return Количество вершин
     */
    size_t getVertexCount() const noexcept { return vertexCount_; }

    /**
     * @brief Добавляет вершину к фигуре.
     * @param vertex Вершина для добавления
     */
    void addVertex(const Point &vertex);

    /**
     * @brief Доступ к вершине по индексу.
     * @param index Индекс вершины
     * @return Ссылка на вершину
     * @throws std::out_of_range Если индекс недопустим
     */
    Point &operator[](size_t index);

    /**
     * @brief Доступ к вершине по индексу.
     * @param index Индекс вершины
     * @return Константная ссылка на вершину
     * @throws std::out_of_range Если индекс недопустим
     */
    const Point &operator[](size_t index) const;

    /**
     * @brief Добавляет вершину к фигуре.
     * @param vertex Вершина для добавления
     * @return Ссылка на эту фигуру
     */
    Figure &operator+=(const Point &vertex);

    /**
     * @brief Поворачивает фигуру вокруг точки на угол (кратный 90 градусам).
     * @param center Центр вращения
     * @param angleDegrees Угол в градусах (должен быть кратен 90)
     * @throws std::invalid_argument Если угол не кратен 90
     */
    void rotate(const Point &center, int angleDegrees);

    friend std::istream &operator>>(std::istream &is, Figure &figure);
    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);
  };

}

#endif