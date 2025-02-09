// ************************************************************************** //
//                                                                            //
//                Account.cpp for GlobalBanksters United                      //
//                Created on  : Tue Nov 20 19:43:15 1989                      //
//                Last update : Tue Sep 10 12:47:06 2024                      //
//                Made by : Brad "Buddy" McLane <bm@gbu.com>                  //
//                                                                            //
// ************************************************************************** //

#include "Account.hpp"

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account( int initial_deposit ) : _accountIndex(_nbAccounts){
	_nbAccounts++;
	_totalAmount += initial_deposit;
	_amount = initial_deposit;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";amount:" << initial_deposit;
	std::cout << ";created\n";
}

Account::~Account( void ){
	_nbAccounts--;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";amount:" << _amount;
	std::cout << ";closed\n";
}

void Account::_displayTimestamp( void ){
	time_t timer;
	struct tm* timeinfo;

	time(&timer);
	timeinfo = localtime(&timer);
	std::cout << "[" << timeinfo->tm_year + 1900;
	if (timeinfo->tm_mon < 10)
		std::cout << "0";
	std::cout << timeinfo->tm_mon;
	if (timeinfo->tm_mday < 10)
		std::cout << "0";
	std::cout << timeinfo->tm_mday;
	if (timeinfo->tm_hour < 10)
		std::cout << "0";
	std::cout << "_" << timeinfo->tm_hour;
	if (timeinfo->tm_min < 10)
		std::cout << "0";
	std::cout << timeinfo->tm_min;
	if (timeinfo->tm_sec < 10)
		std::cout << "0";
	std::cout << timeinfo->tm_sec << "] ";
}

int		Account::getNbAccounts( void ){

	return (_nbAccounts);
}

int		Account::getNbDeposits( void ){

	return (_totalNbDeposits);
}

int		Account::getTotalAmount( void ){

	return (_totalAmount);
}

int		Account::getNbWithdrawals( void ){
	return (_totalNbWithdrawals);
}


int		Account::checkAmount( void ) const{
	return (_amount);
}

void	Account::displayAccountsInfos( void ){
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts();
	std::cout << ";total:" << getTotalAmount();
	std::cout << ";deposits:" << getNbDeposits();
	std::cout << ";withdrawals:" << getNbWithdrawals() << "\n";
}

void	Account::displayStatus( void ) const{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";amount:" << _amount;
	std::cout << ";deposits:" << _nbDeposits;
	std::cout << ";withdrawals:" << _nbWithdrawals;
	std::cout << "\n";
	return ;
}

void	Account::makeDeposit( int deposit ) {
	int p_amount = _amount;

	_totalAmount += deposit;
	_totalNbDeposits++;
	_nbDeposits = 1;
	_amount += deposit;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";p_amount:" << p_amount;
	std::cout << ";deposit:" << deposit;
	std::cout << ";amount:" << _amount;
	std::cout << ";nb_deposits:" << _nbDeposits;
	std::cout << "\n";
	return ;
}

bool	Account::makeWithdrawal( int withdawal ){
	if (withdawal > checkAmount())
	{
		_displayTimestamp();
		std::cout << "index:" << _accountIndex;
		std::cout << ";p_amount:" << _amount;
		std::cout << ";withdrawal:refused\n";
		return (false);
	}
	int p_amount = _amount;
	_totalAmount -= withdawal;
	_totalNbWithdrawals++;
	_nbWithdrawals = 1;
	_amount -= withdawal;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";p_amount:" << p_amount;
	std::cout << ";withdrawal:" << withdawal;
	std::cout << ";amount:" << _amount;
	std::cout << ";nb_withdrawals:" << _nbWithdrawals;
	std::cout << "\n";
	return (true);
}

