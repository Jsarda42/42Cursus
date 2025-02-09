#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain constructor called" << std::endl;
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& rhs)
{
	std::cout << "Brain assignation operator called" << std::endl;
	if (this == &rhs)
		return (*this);
	for (int i = 0; i < 100; i++)
		ideas_[i] = rhs.ideas_[i];
	return (*this);
}

Brain::Brain(const Brain& cpy)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = cpy;
}

std::string Brain::getIdeas(int index) const
{
	return (this->ideas_[index]);
}

void Brain::setIdeas(std::string idea)
{
	for (int i = 0; i < 100; i++)
	{
		ideas_[i] = idea;
	}
}
