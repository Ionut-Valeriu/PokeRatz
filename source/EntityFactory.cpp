//
// Created by ionut on 12.01.2025.
//

template <class E>
template <typename T>
std::shared_ptr<E> EntityFactory<E>::addEntity(const size_t &id, size_t drawLevel) {
    auto e = std::make_shared<T>(id, drawLevel);
    return e;
}

template <class E>
std::shared_ptr<E> EntityFactory<E>::makeEntity(char type, size_t id, size_t drawLevel) {
    switch (type) {
        case '-': return nullptr;

        case 'P': return addEntity<Player>(id, drawLevel);

        case 'M': return addEntity<Monster>(id, drawLevel);

        case 'B': return addEntity<Background>(id, drawLevel);

        case 'I': return addEntity<Illusion>(id, drawLevel);

        default: throw std::invalid_argument("Invalid type: " + std::to_string(type));
    }
}
