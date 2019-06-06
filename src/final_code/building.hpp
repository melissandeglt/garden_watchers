#pragma once

class Building {
public:
    Building(float m_portee, float m_type);
    ~Building();

    /* Getters */
    float getPortee() const { return m_portee; }
    float getType() const { return m_type; }

    /* Setters */
    void setPortee(float port) { m_portee = port; }
    void setType(float type) { m_type = type; }
    void ActionCircle();
    void Ameliorer();

private:
    float m_portee;
    float m_type;
};