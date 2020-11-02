//0. Предметная область.От 10 различных информационных объектов, коммуницирующих между собой.
//1. Обязательно использование наследования, полиморфизма, инкапсуляции
//2. Диаграмма UML
//3. Реализация на C++
//4. Соблюдение принципов SOLID
//5. Использовать хотя бы один паттерн ООП.
#include <iostream>
using namespace std;


class Processor
{
public:
	/*friend class LowCostProcessor;
	friend class GamingProcessor;
private:*/
	string name;
	unsigned int frequency;
	unsigned int cores;
	unsigned int cost;

	void print() {
		cout << "Processor:" << name << endl
			<< " Frequency: " << frequency << endl
			<< " Cores: " << cores << endl
			<< " Cost: " << cost << endl;
	}
	unsigned int printCost() {
		return cost;
	}
};

class VideoCard
{
public:
	string name;
	unsigned int memory;
	unsigned int cost;

	void print() {
		cout << "Videocard:" << name << endl
			<< " Memory: " << memory << endl
			<< " Cost: " << cost << endl;
	}
	unsigned int printCost() {
		return cost;
	}
};

class ComputerParts
{
public:
	void setProccessor(Processor* processor) {
		this->processor = processor;
	}
	void setVideoCard(VideoCard* videocard) {
		this->videocard = videocard;
	}
	void print() {
		this->processor->print();
		this->videocard->print();
	}
private:
	VideoCard* videocard;
	Processor* processor;
	//Peripheral* peripheral;
	unsigned int cost = 0;
};

class ProcessorBuilder {
public:

	virtual void getName() const = 0;
	virtual void getFrequency() const = 0;
	virtual void getCores() const = 0;
	virtual void getCost() const = 0;
};

class LowCostProcessor : public ProcessorBuilder
{
public:
	void getName()const override {
		this->processor->name = "Intel Core i3-7100";
	}
	void getFrequency()const override {
		this->processor->frequency = 3000;
	}
	void getCores()const override {
		this->processor->cores = 2;
	}
	void getCost()const override {
		this->processor->cost = 5000;
	}
	Processor* returnProc() {
		return processor;
	}
private:
	Processor* processor;
};


class GamingProcessor : public ProcessorBuilder
{
public:
	void getName()const override {
		this->processor->name = "Intel Core i7-8700K";
	}
	void getFrequency()const override {
		this->processor->frequency = 4500;
	}
	void getCores()const override {
		this->processor->cores = 4;
	}
	void getCost()const override {
		this->processor->cost = 15000;
	}
	Processor* returnProc() {
		return processor;
	}
private:
	Processor* processor;
};

class VideoCardBuilder {
public:
	virtual void getName() const = 0;
	virtual void getMemory() const = 0;
	virtual void getCost() const = 0;
};

class LowCostVideoCard : public VideoCardBuilder
{
public:
	
	void getName()const override {
		this->videocard->name = "NVidia GeForce 1050";
	}
	void getMemory()const override {
		this->videocard->memory = 2;
	}
	void getCost()const override {
		this->videocard->cost = 7000;
	}
	VideoCard* returnVideoCard() {
		return videocard;
	}
private:
	VideoCard* videocard;
};


class GamingVideoCard : public VideoCardBuilder
{
public:
	void getName()const override {
		this->videocard->name = "NVidia GeForce 3080";
	}
	void getMemory()const override {
		this->videocard->memory = 10;
	}
	void getCost()const override {
		this->videocard->cost = 50000;
	}
	VideoCard* returnVideoCard() {
		return videocard;
	}
private:
	VideoCard* videocard;
};


//class Peripheral
//{
//public:
//
//
//private:
//	string peripheral = "mouse, keyboard, monitor";
//};


class Builder
{
public:
	virtual Processor* getProcessor() = 0;
	virtual VideoCard* getVideoCard() = 0;
	//virtual Peripheral* getPeripheral() = 0;
};


class Director
{
	Builder* builder;

public:
	void setBuilder(Builder* newBuilder)
	{
		builder = newBuilder;
	}

	ComputerParts* getComputer()
	{
		ComputerParts* computer = new ComputerParts();
		computer;
		


		return computer;
	}
};

class GamingComputer : public Builder
{
public:
	Processor* getProcessor() {
		GamingProcessor* processor = new GamingProcessor;
		processor->getName();
		processor->getCores();
		processor->getFrequency();
		processor->getCost();
		return processor->returnProc();
	}

	VideoCard* getVideoCard() {
		GamingVideoCard* videoard = new GamingVideoCard;
		videoard->getName();
		videoard->getMemory();
		videoard->getCost();
		return videoard->returnVideoCard();
	}
private:

};

class OfficeComputer : public Builder
{
public:
	Processor* getProcessor() {
		LowCostProcessor* processor = new LowCostProcessor;
		processor->getName();
		processor->getCores();
		processor->getFrequency();
		processor->getCost();
		return processor->returnProc();
	}

	VideoCard* getVideoCard() {
		LowCostVideoCard* videoard = new LowCostVideoCard;
		videoard->getName();
		videoard->getMemory();
		videoard->getCost();
		return videoard->returnVideoCard();
	}
private:

};


void ClientCode(Director& director)
{
	GamingComputer* builder = new GamingComputer;
	director.setBuilder(builder);
	cout << "Gaming computer:" << endl;
	

	ComputerParts* p = builder->getComputer();
	p->print();
	delete p;

	//std::cout << "Standard full featured product:\n";
	//director.BuildFullFeaturedProduct();

	//p = builder->GetProduct();
	//p->ListParts();
	//delete p;

	//// Помните, что паттерн Строитель можно использовать без класса Директор.
	//std::cout << "Custom product:\n";
	//builder->ProducePartA();
	//builder->ProducePartC();
	//p = builder->GetProduct();
	//p->ListParts();
	//delete p;

	delete builder;
}
int main() {
	Director* director = new Director();
	ClientCode(*director);
	delete director;
	return 0;
}