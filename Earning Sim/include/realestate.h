#ifndef REALESTATE_H
#define REALESTATE_H

#include <string>
#include <vector>
namespace REALESTATE
{
  class Property
  {
  private : 
     std::string propertyName;
     double propertyPrice;
     bool owned;
  public :
      void setProperty(std::string name, double price, bool own);

      void changePrice(double price);//Pass final price

      bool isOwned();
      std::string getPropertyName();
      double getPropertyPrice();
      void setOwned(bool o);

      void showInfo();
  };

   class RealEstate
   {
   private:
      std::vector<Property> properties;
      int totalProperties;
      int totalOwnedProperties;
   public:
     // RealEstate(std::vector<std::string> names, std::vector<double> prices);
      RealEstate();
      ~RealEstate();

      void buyProperty(int i);
      void sellProperty(int i);

      void realEstate(); // Main function showing menu

   void displayAllProperties();
   void displayOwnedProperties();
   void displayUnownedProperties();

      void fluctuatePrice();

   void saveData();
   void loadData(); //This function will also be responsible to load and set property values
   };

   
}

#endif