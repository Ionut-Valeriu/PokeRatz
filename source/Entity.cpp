//
// Created by ionut on 22.10.2024.
//

#include "Entity.h"

Entity::Entity(const size_t id, std::string tag, const size_t drawLevel = 1)
    : m_tag(std::move(tag)), m_id(id), m_drawLevel(drawLevel) {
    // init();
}

void Entity::init() {
    // m_transform = std::make_shared<CTransform>(sf::Vector2f{200, 200},
    // sf::Vector2f{0, 0}, sf::Vector2f{5.0f, 5.0f});

    m_transform = std::make_shared<CTransform>();
    m_boundingBox = std::make_shared<CBoundingBox>();

    tempShape = std::make_shared<sf::RectangleShape>(sf::Vector2f{80, 80});
    tempShape->setFillColor({0, 0, 0, 0}); // transparent interor/fill
    tempShape->setOutlineColor(sf::Color{255, 255, 255, 255}); // white outline
    tempShape->setOutlineThickness(1); // dimension of the outline

    tempShape->setOrigin(sf::Vector2f(tempShape->getSize() / 2.0f));


    m_origin = std::make_shared<sf::CircleShape>(5.0f);
    m_origin->setFillColor(sf::Color{255, 255, 255, 255});
    m_origin->setOrigin(sf::Vector2f(m_origin->getRadius() / 2.0f, m_origin->getRadius() / 2.0f));
    m_origin->setPosition(tempShape->getPosition());
}

void Entity::setRect(sf::IntRect rect) {
    // m_rectttt = rect;
    m_boundingBox->setBoundingRect(rect);
    m_animation->setRect(rect);

    tempShape->setSize(sf::Vector2f(rect.width * m_animation->getSprite().getScale().x,
                                    rect.height * m_animation->getSprite().getScale().y));

    // tempShape->setSize(sf::Vector2f(rect.width ,rect.height ));
    tempShape->setOrigin(sf::Vector2f(tempShape->getSize().x / 2, tempShape->getSize().y / 2));

    // m_origin->setPosition(tempShape->getPosition());
}

void Entity::draw(sf::RenderWindow &window, bool s, bool r, bool o) const {
    tempShape->setPosition(m_transform->getPosition());
    m_origin->setPosition(m_animation->getSprite().getPosition());

    m_animation->getSprite().setPosition(m_transform->getPosition());

    if (s) { window.draw(m_animation->getSprite()); }
    if (r) { window.draw(*tempShape); }
    if (o) { window.draw(*m_origin); }
}

std::shared_ptr<Animation> Entity::getAnimation() const {
    return m_animation;
}

bool Entity::collide(const Entity &other) const {
    auto p = tempShape->getSize();
    auto o = other.tempShape->getSize();
    sf::Vector2f hp = {p.x / 2, p.y / 2};
    sf::Vector2f ho = {o.x / 2, o.y / 2};

    auto dx = abs(m_transform->getPosition().x - other.m_transform->getPosition().x);
    auto dy = abs(m_transform->getPosition().y - other.m_transform->getPosition().y);

    if (hp.x + ho.x > dx && hp.y + ho.y > dy) {
        return true;
    }
    return false;
}

float Entity::getX() const { return m_transform->getPosition().x; }
float Entity::getY() const { return m_transform->getPosition().y; }

float Entity::getWidth() const {
    return tempShape->getSize().x;
}

float Entity::getHeight() const {
    return tempShape->getSize().y;
}

void Entity::setScale(const sf::Vector2f &scale) const {
    m_transform->setScale(scale);
    // m_animation->setScale(scale);
    // tempShape->setSize({ tempShape->getSize().x * scale.x, tempShape->getSize().y * scale.y });
    // tempShape->setScale(scale);
    // tempShape->setOutlineThickness(1);
}

sf::Vector2f Entity::getScale() const {
    return m_transform->getScale();
}

void Entity::setPosition(const sf::Vector2f &position) const {
    m_transform->setPosition(position);
    // tempShape->setPosition(m_transform->getPosition());
    // m_origin->setPosition(tempShape->getOrigin());
}

void Entity::setBorderT(const int thickness) const {
    tempShape->setOutlineThickness(static_cast<float>(thickness));
}

void Entity::updatePos() const {
    if (m_transform->has()) {
        m_transform->updatePos();
    }
}

void Entity::updateAnimation() const { m_animation->update(); }

bool Entity::isSolid() const { return m_solid; }

// bool Entity::isRemovable() const {
//     return m_removable;
// }

void Entity::setAnimation(Animation &anim) {
    m_animation = std::make_shared<Animation>(anim);
}

void Entity::setState(const State &state) {
    m_state = state;
}

void Entity::remove() { m_active = false; }

std::ostream &operator<<(std::ostream &os, const Entity &obj) {
    os << "Type: ";

    obj.showTip(os);

    os << "\n m_id: " << obj.m_id << "; m_tag: " << obj.m_tag
            << "\n m_transform: " << obj.m_transform->getPosition().x
            << "\n tempShape: " << obj.tempShape << " size: " << sizeof(obj.tempShape)
            << "\n m_active: " << obj.m_active << " size: " << sizeof(obj.m_active)
            << "\n animation:" << obj.m_animation << "\n";

    return os;
}

void Entity::showTip(std::ostream &os) const {
    os << "Entity\n";
}
