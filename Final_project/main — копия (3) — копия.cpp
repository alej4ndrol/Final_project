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
	void setVideoCard(VideoCard* videocard) {
		this->videocard = videocard;
		this->cost += videocard->printCost();
	}
	void setProcessor(Processor* processor) {
		this->processor = processor;
		this->cost += processor->printCost();
	}
	/*void setPeripheral(Peripheral* peripheral) {
		this->peripheral = peripheral;
	}*/
	void print() {
		this->processor->print();
		this->videocard->print();
		this->printCost();
	}
	unsigned int printCost() {
		return this->cost;
	}
	void incCost(int addCost) {
		this->cost += addCost;
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
	LowCostProcessor() {
		this->Reset();
	}

	~LowCostProcessor() {
		delete processor;
	}

	void Reset() {
		this->processor = new Processor();
	}

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
	Processor* GetProduct() {
		Processor* result = this->processor;
		this->Reset();
		return result;
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
	LowCostVideoCard() {
		this->Reset();
	}

	~LowCostVideoCard() {
		delete videocard;
	}

	void Reset() {
		this->videocard = new VideoCard();
	}

	void getName()const override {
		this->videocard->name = "NVidia GeForce 1050";
	}
	void getMemory()const override {
		this->videocard->memory = 2;
	}
	void getCost()const override {
		this->videocard->cost = 7000;
	}
	VideoCard* GetProduct() {
		VideoCard* result = this->videocard;
		this->Reset();
		return result;
	}
private:
	VideoCard* videocard;
};


class GamingVideoCard : public VideoCardBuilder
{
public:
	GamingVideoCard() {
		this->Reset();
	}

	~GamingVideoCard() {
		delete videocard;
	}

	void Reset() {
		this->videocard = new VideoCard();
	}

	void getName()const override {
		this->videocard->name = "NVidia GeForce 3080";
	}
	void getMemory()const override {
		this->videocard->memory = 10;
	}
	void getCost()const override {
		this->videocard->cost = 50000;
	}
	VideoCard* GetProduct() {
		VideoCard* result = this->videocard;
		this->Reset();
		return result;
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
	virtual int incCost() = 0;
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

		computer->setProcessor(builder->getProcessor());
		computer->incCost(builder->getProcessor()->printCost());
		computer->setVideoCard(builder->getVideoCard());
		computer->incCost(builder->getVideoCard()->printCost());

		//computer->setPeripheral(builder->getPeripheral());


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
		return processor->GetProduct();
	}

	VideoCard* getVideoCard() {
		GamingVideoCard* videoard = new GamingVideoCard;
		videoard->getName();
		videoard->getMemory();
		videoard->getCost();
		return videoard->GetProduct();
	}
	/*int incCost() {

	}*/
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
		return processor->GetProduct();
	}

	VideoCard* getVideoCard() {
		LowCostVideoCard* videoard = new LowCostVideoCard;
		videoard->getName();
		videoard->getMemory();
		videoard->getCost();
		return videoard->GetProduct();
	}
private:

};


//void ClientCode(Director& director)
//{
//	GamingComputer* GamingBuilder = new GamingComputer;
//	director.setBuilder(GamingBuilder);
//	cout << "Gaming computer:" << endl;
//
//
//	Computer* p = director.getComputer();
//	p->print();
//	delete p;
//
//	OfficeComputer* OfficeBuilder = new OfficeComputer;
//	director.setBuilder(OfficeBuilder);
//	cout << "Office computer:" << endl;
//
//
//	p = director.getComputer();
//	p->print();
//	delete p;
//
//
//	delete OfficeBuilder;
//	delete GamingBuilder;
//}
int main() {
	Director* director = new Director();
	//ClientCode(*director);
	GamingComputer* GamingBuilder = new GamingComputer;
	director->setBuilder(GamingBuilder);
	cout << "Gaming computer:" << endl;

	ComputerParts* varPrint = director->getComputer();
	varPrint->print();
	//delete varPrint;

	OfficeComputer* OfficeBuilder = new OfficeComputer;
	director->setBuilder(OfficeBuilder);
	cout << endl << "Office computer:" << endl;


	/*ComputerParts**/ varPrint = director->getComputer();
	varPrint->print();
	delete varPrint;


	delete OfficeBuilder;
	delete GamingBuilder;
	delete director;
	return 0;
}