//0. Предметная область.От 10 различных информационных объектов, коммуницирующих между собой. 
//1. Обязательно использование наследования, полиморфизма, инкапсуляции
//2. Диаграмма UML
//3. Реализация на C++
//4. Соблюдение принципов SOLID
//5. Использовать хотя бы один паттерн ООП.
//0+
//1+
//2+
//3+
//4++-
//5+
#include <iostream>
using namespace std;

class Processor//часть компа
{
public:
	
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


class VideoCard//часть компа
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



class ComputerParts//продукт
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
	void print() {
		this->processor->print();
		this->videocard->print();
		this->printCost();
	}
	void printCost() {
		cout << "Parts cost: " << this->cost << endl;
	}
private:
	VideoCard* videocard;
	Processor* processor;
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

class Builder
{
public:
	virtual Processor* getProcessor() = 0;
	virtual VideoCard* getVideoCard() = 0;
};


class Director
{
	Builder* builder;

public:
	void setBuilder(Builder* newBuilder){
		builder = newBuilder;
	}

	ComputerParts* getComputer(){
		ComputerParts* computer = new ComputerParts();

		computer->setProcessor(builder->getProcessor());
		computer->setVideoCard(builder->getVideoCard());
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

int main() {
	Director* director = new Director();
 
	GamingComputer* GamingBuilder = new GamingComputer;
	director->setBuilder(GamingBuilder);
	cout << "Gaming computer:" << endl;

	ComputerParts* varPrint = director->getComputer();
	varPrint->print();

	OfficeComputer* OfficeBuilder = new OfficeComputer;
	director->setBuilder(OfficeBuilder);
	cout << endl << "Office computer:" << endl;

	varPrint = director->getComputer();
	varPrint->print();
	delete varPrint;

	//
	delete OfficeBuilder;
	delete GamingBuilder;
	delete director;
	return 0;
}
