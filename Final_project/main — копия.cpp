//0. Предметная область.От 10 различных информационных объектов, коммуницирующих между собой.
//1. Обязательно использование наследования, полиморфизма, инкапсуляции
//2. Диаграмма UML
//3. Реализация на C++
//4. Соблюдение принципов SOLID
//5. Использовать хотя бы один паттерн ООП.
#include <iostream>
using namespace std;

class Computer
{
public:
	Computer(VideoCard videocard, Processor processor, Peripheral peripheral) {
		this->videocard = videocard;
		this->processor = processor;
		this->peripheral = peripheral;
	}
private:
	VideoCard videocard;
	Processor processor;
	Peripheral peripheral;
	unsigned int cost = 0;
};


class Processor
{
public:
	/*friend class LowCostProcessor;
	friend class GamingProcessor;
private:*/
	unsigned int frequency;
	unsigned int cores;
	unsigned int cost;

	string print() {
		cout << "Processor:" << endl
			<< " Frequency " << frequency << endl
			<< " cores " << cores << endl
			<< " cost " << cost << endl;
	}
};

class ProcessorBuilder {
public:
	virtual ~ProcessorBuilder() {}
	virtual void setFrequency() const = 0;
	virtual void setCores() const = 0;
	virtual void setCost() const = 0;
};

class LowCostProcessor : public ProcessorBuilder
{
public:
	LowCostProcessor() {
		this->Reset();
	}

	~LowCostProcessor() {
		delete processor;
	}

	void Reset() {
		this->processor = new Processor();
	}

	void setFrequency()const override {
		this->processor->frequency = 3000;
	}
	void setFrequency()const override {
		this->processor->cores = 2;
	}
	void setFrequency()const override {
		this->processor->cost = 5000;
	}
	Processor* GetProduct() {
		Processor* result = this->processor;
		this->Reset();
		return result;
	}
private:
	Processor* processor;
};


class GamingProcessor : public ProcessorBuilder
{
public:
	GamingProcessor() {
		this->Reset();
	}

	~GamingProcessor() {
		delete processor;
	}

	void Reset() {
		this->processor = new Processor();
	}

	void setFrequency()const override {
		this->processor->frequency = 3000;
	}
	void setFrequency()const override {
		this->processor->cores = 2;
	}
	void setFrequency()const override {
		this->processor->cost = 5000;
	}
	Processor* GetProduct() {
		Processor* result = this->processor;
		this->Reset();
		return result;
	}
private:
	Processor* processor;
};


class VideoCard
{
public:


private:

};

class VideoCardBuilder {
public:
	virtual ~VideoCardBuilder() {}
	virtual void setFrequency() const = 0;
	virtual void setCores() const = 0;
	virtual void setCost() const = 0;
};

class Peripheral
{
public:


private:

};


class Builder
{
public:


private:

};

class Laptop : public Builder
{
public:

private:

};


class GamingComputer : public Builder
{
public:

private:

};

class ServerComputer : public Builder
{
public:

private:

};

int main() {


	return 0;
}