#ifndef IN_MEMORY_CAR_REPOSITORY_H
#define IN_MEMORY_CAR_REPOSITORY_H

#include "CarRepository.h"
#include <list>

namespace repository {
	class InMemoryCarRepository : public repository::CarRepository
    {
	public:
        ~InMemoryCarRepository();
        InMemoryCarRepository(InMemoryCarRepository&) = delete;
        void operator=(const InMemoryCarRepository&) = delete;
        static InMemoryCarRepository* getInstance();
        virtual void save(const domain::Car&);
        virtual std::vector<domain::Car> getAllCars() const;
    private:
        static InMemoryCarRepository* instance;
        InMemoryCarRepository() = default;
        std::list<domain::Car> cars;
	};
}

#endif // !IN_MEMORY_CAR_REPOSITORY_H
