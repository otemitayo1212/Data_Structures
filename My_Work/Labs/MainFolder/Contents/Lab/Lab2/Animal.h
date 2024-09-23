class Animal {
public:
    // Constructor: Initializes an Animal with a given name
    Animal(const std::string& name);

    // Function to set the weight of the animals and other parts
    void setWeight(double theweight);

    void setSurviveOnLand ( bool aland );

    void canSurviveInWater( bool awater)

    void  eatsMeat(bool ameat) ;

    void eatsPlants(bool aplant);

    void print() const;

    std:: string getName () const;

    double getWeight () const;
     

    // Function to check if the animal can survive on land
    bool canSurviveOnLand() const;

    // Function to check if the animal can survive in water
    bool canSurviveInWater() const ;

    // Function to check if the animal eats meat
    bool eatsMeat() const;

    // Function to check if the animal eats plants
    bool eatsPlants() const;

    // Function to check if the animal is an omnivore (eats both meat and plants)
    bool isOmnivore() const;

    // Function to check if the animal is amphibious (can survive on land and in water)
    bool isAmphibious() const;

    // Function to get the name of the animal
    std::string getName() const;

private:
    std::string name;
    double weight;
    bool surviveOnLand;
    bool surviveInWater;
    bool eatMeat;
    bool eatPlants;
};