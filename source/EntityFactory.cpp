//
// Created by ionut on 12.01.2025.
//

template<class T>
std::shared_ptr<Entity> EntityFactory::addEntity(const size_t &id) {
    auto e = std::make_shared<T>(id, 1);
    return e;
}

std::shared_ptr<Entity> EntityFactory::makeEntity(char type, size_t id) {
    switch (type) {
        case '-': return nullptr;

        case 'P': return addEntity<Player>(id);

        case 'M': return addEntity<Monster>(id);

        case 'B': return addEntity<Background>(id);

        default: throw std::invalid_argument("Invalid type: " + std::to_string(type));
    }
}
