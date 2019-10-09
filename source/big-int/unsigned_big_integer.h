#pragma once

#include <string>
#include <algorithm>

class unsigned_big_integer
{
public:
	unsigned_big_integer() = default;
	unsigned_big_integer(const std::string& number)
	{
		if (number.empty())
			throw std::exception("incorrect number");

		for (const char symbol : number)
		{
			if(unsigned_big_integer::dec_digits.find(symbol) == std::string::npos)
				throw std::exception("incorrect number");
		}

		this->_value = number;
	}
	unsigned_big_integer(const uint32_t number) : unsigned_big_integer(std::to_string(number)) {}
	unsigned_big_integer(const uint64_t number) : unsigned_big_integer(std::to_string(number)) {}

	[[nodiscard]] unsigned_big_integer sum (const unsigned_big_integer& n) const
	{
		std::string first_number_copy = this->_value;
		std::string second_number_copy = n._value;
		
		if (first_number_copy.size() < second_number_copy.size())
			first_number_copy.swap(second_number_copy);

		const size_t max_size = first_number_copy.size();
		const size_t min_size = second_number_copy.size();
		
		std::string sum = first_number_copy;
		uint8_t carry = 0;
		
		for (size_t i = 0; i < min_size; i++)
		{
			const char first_symbol = first_number_copy[max_size - i - 1];
			const char second_symbol = second_number_copy[min_size - i - 1];

			const uint8_t first_symbol_value = first_symbol - '0';
			const uint8_t second_symbol_value = second_symbol - '0';

			const uint8_t symbols_value_sum = static_cast<uint8_t>(first_symbol_value + second_symbol_value + carry);

			carry = symbols_value_sum > 9;

			const char result_symbol = static_cast<char>('0' + symbols_value_sum % 10);

			sum[max_size - i - 1] = result_symbol;
		}

		for(size_t i = min_size; i < max_size && carry != 0; i++)
		{
			const char first_symbol = first_number_copy[max_size - 1 - i];

			const uint8_t first_symbol_value = first_symbol - '0';

			const uint8_t symbol_value_sum = static_cast<uint8_t>(first_symbol_value + carry);

			carry = symbol_value_sum > 9;

			const char result_symbol = static_cast<char>('0' + symbol_value_sum % 10);

			sum[max_size - 1 - i] = result_symbol;
		}

		if (carry != 0)
			sum.insert(0, 1, carry + '0');
		
		return sum;
	}
	[[nodiscard]] unsigned_big_integer sub (const unsigned_big_integer& n) const
	{
		std::string first_number_copy = this->_value;
		std::string second_number_copy = n._value;

		if (first_number_copy.size() < second_number_copy.size()
			|| (first_number_copy.size() == second_number_copy.size() && 
			    first_number_copy.front() < second_number_copy.front()))
			throw std::exception();
		
		if (first_number_copy.size() < second_number_copy.size())
			first_number_copy.swap(second_number_copy);

		const size_t max_size = first_number_copy.size();
		const size_t min_size = second_number_copy.size();

		for(size_t i = 0; i < min_size; i++)
		{
			const char first_symbol = first_number_copy[max_size - min_size + i];
			const char second_symbol = second_number_copy[i];

			const uint8_t first_symbol_value = first_symbol - '0';
			const uint8_t second_symbol_value = second_symbol - '0';

			const bool first_is_low_then_second = first_symbol_value < second_symbol_value;
			
			if(first_is_low_then_second)
				--first_number_copy[max_size - min_size + i - 1];

			first_number_copy[max_size - min_size + i] = '0' + first_symbol_value - second_symbol_value + 10 * first_is_low_then_second;
		}

		align::right(first_number_copy);
		return first_number_copy;
	}
	[[nodiscard]] unsigned_big_integer mul(const unsigned_big_integer& n) const
	{
		return {};
	}
	[[nodiscard]] unsigned_big_integer div(size_t n) const
	{
		if (n == 0)
			throw std::exception();
		if (n == 1)
			return *this;

		std::string ans, number = this->_value;
		uint32_t idx = 0;
		uint32_t temp = number[idx] - '0';

		while (temp < n)
			temp = temp * 10 + (number[++idx] - '0');

		while (number.size() > idx)
		{
			ans.push_back(temp / n + '0');

			temp = (temp % n) * 10 + number[++idx] - '0';
		}

		if (ans.length() == 0)
			return static_cast<std::string>("0");

		return ans;
	}
	
	[[nodiscard]] std::string to_string() const
	{
		return  this->_value;
	}
	
private:
	std::string _value = "0";
	inline static const std::string dec_digits = "1234567890";
	inline static const std::string zero = "0";

	struct align
	{
		static void right(std::string& number)
		{
			for(size_t i = number.size() - 1; i != 0; i--)
			{
				if(number[i] != '0')
				{
					number.resize(i + 1);
					return;
				}
			}

			number.resize(1);
		}
	};
};
