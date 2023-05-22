#define TEST
#include "doctest.h"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"

/// @brief 
/// providing mock class for character for checking default Character functions as Character is pure virtual
namespace ariel {
    class MockCharacter : public Character {
        public:
            MockCharacter(Point loc, int hp, std::string name) : Character(loc, hp, name) {}

            std::string print() override {
                return "MockCharacter: " + getName();
            }
        };
    }
using namespace ariel;
TEST_SUITE("Point Class"){
    TEST_CASE("Point initialization") {
        ariel::Point p(3.5, 2.8);
        CHECK(p.getX() == 3.5);
        CHECK(p.getY() == 2.8);
    }

    TEST_CASE("Point distance") {
        ariel::Point p1(0, 0);
        ariel::Point p2(3, 4);
        CHECK(p1.distance(p2) == 5);
        CHECK(p2.distance(p1) == 5);
    }

    TEST_CASE("Point moveTowards") {
        ariel::Point p1(0, 0);
        ariel::Point p2(3, 4);
        p1.moveTowards(p2);
        CHECK(p1.getX() == doctest::Approx(1.8).epsilon(0.01));
        CHECK(p1.getY() == doctest::Approx(2.4).epsilon(0.01));
        p1.moveTowards(p2);
        CHECK(p1.getX() == doctest::Approx(2.4).epsilon(0.01));
        CHECK(p1.getY() == doctest::Approx(3.2).epsilon(0.01));
    }
}
TEST_SUITE("Character interface test"){
    TEST_CASE("Test isAlive function") {
        Point loc(0, 0);
        int health = 100;
        string name = "TestCharacter";
        MockCharacter c(loc, health, name);
        CHECK(c.isAlive() == true);
        c.hit(health);
        CHECK(c.isAlive() == false);
    }

    TEST_CASE("Test distance function") {
        Point loc1(0, 0);
        Point loc2(3, 4);
        int health = 100;
        string name = "TestCharacter";
        MockCharacter c1(loc1, health, name);
        MockCharacter c2(loc2, health, name);
        CHECK(c1.distance(c2) == doctest::Approx(5.0));
    }

    TEST_CASE("Test hit function") {
        Point loc(0, 0);
        int health = 100;
        string name = "TestCharacter";
        MockCharacter c(loc, health, name);
        int damage = 50;
        c.hit(damage);
        CHECK(c.isAlive() == true);
        CHECK(c.getHealth() == (health - damage));
    }

    TEST_CASE("Test getName and getLocation functions") {
        Point loc(0, 0);
        int health = 100;
        string name = "TestCharacter";
        MockCharacter c(loc, health, name);
        CHECK(c.getName() == name);
        CHECK(c.getLocation().distance(loc) == 0);
    }

    TEST_CASE("Test print function") {
        Point loc(0, 0);
        int health = 100;
        string name = "TestCharacter";
        MockCharacter c(loc, health, name);
        string expected = "Name: TestCharacter\nHealth: 100\nLocation: (0, 0)";
        CHECK(c.print() == expected);
    }
}
TEST_SUITE("Ninja class tests"){
    TEST_CASE("test movement") {
        // Create two Ninja objects and move one towards the other
        Point p1(0, 0);
        Point p2(10, 10);
        OldNinja n1("Ninja 1", p1);
        OldNinja n2("Ninja 2", p2);
        double dist = n1.distance(n2);
        n1.move(&n2);
        double newDist = n1.distance(n2);
        CHECK(newDist < dist); // make sure the distance was reduced
    }

    TEST_CASE("test attack") {
        // Create two Ninja objects and have one attack the other
        Point p1(0, 0);
        Point p2(10, 10);
        OldNinja n1("Ninja 1", p1);
        OldNinja n2("Ninja 2", p2);
        int healthBefore = n2.getHealth();
        n1.slash(&n2);
        int healthAfter = n2.getHealth();
        CHECK(healthAfter < healthBefore); // make sure the health was reduced
    }

    TEST_CASE("test print") {
        // Create a Ninja object and check its print output
        Point p(0, 0);
        OldNinja n("Ninja",p);
        std::string expectedOutput = "Ninja (100 HP) at (0,0) with speed 10";
        CHECK(n.print() == expectedOutput);
    }
}
TEST_SUITE("Cowboy class tests")
{
    Point p1(0,0);
    Cowboy c1("Cowboy", p1);
    MockCharacter enemy(p1, 100, "Enemy");
    void before_each(){
        Cowboy c1("Cowboy", p1);
        MockCharacter enemy(p1, 100, "Enemy");
    }
    
    TEST_CASE("Test constructor") {
        before_each();
        CHECK(c1.getName() == "Cowboy");
        CHECK(c1.getLocation().distance(p1) == 0);
        CHECK(c1.isAlive());
        CHECK(c1.hasboolets());
    }
    TEST_CASE("Test shoot and hasboolets") {
        before_each();
        CHECK(c1.hasboolets());
        for (size_t i = 0; i < 6; i++){
            c1.shoot(&enemy);    
        }
        CHECK_FALSE(c1.hasboolets());
    }
    TEST_CASE("Test reload") {
        before_each();
        CHECK(c1.hasboolets());
        for (size_t i = 0; i < 6; i++){c1.shoot(&enemy);}
        CHECK_FALSE(c1.hasboolets());
        c1.reload();
        CHECK(c1.hasboolets());
    }
}
TEST_SUITE("OldNinja Tests"){
    TEST_CASE("Test constructor and inherited properties from Ninja")
    {
        ariel::Point loc1{1,1};
        OldNinja on1{"Old Ninja 1", loc1};
        CHECK(on1.getName() == "Old Ninja 1");
        CHECK(on1.getLocation().distance(loc1) == 0);
        CHECK(on1.isAlive());
        CHECK(on1.getHealth() == 150);
        CHECK(on1.getSpeed() == 8);
    }
    
    TEST_CASE("Test inherited functions from Ninja")
    {
        ariel::Point loc1{1,1};
        ariel::Point loc2{10,10};
        OldNinja on1{"Old Ninja 1", loc1};
        OldNinja on2{"Old Ninja 2", loc2};
        CHECK(on1.distance(on2) == doctest::Approx(12.73).epsilon(0.01));
        on1.move(&on2);
        CHECK(on1.getLocation().distance(loc2) == doctest::Approx(4.73).epsilon(0.01));
        // move again so we can slash
        on1.move(&on2); 
        on1.slash(&on2);
        CHECK(on2.getHealth() == (119));
        on1.hit(30);
        CHECK(on1.getHealth() == 120);
    }
}
TEST_SUITE("TrainedNinja Tests"){
    TEST_CASE("Test constructor and inherited properties from Ninja")
    {
        ariel::Point loc1{1,1};
        TrainedNinja tn1{"Trained Ninja 1", loc1};
        CHECK(tn1.getName() == "Trained Ninja 1");
        CHECK(tn1.getLocation().distance(loc1) == 0);
        CHECK(tn1.isAlive());
        CHECK(tn1.getHealth() == 120);
        CHECK(tn1.getSpeed() == 12);
    }
    
    TEST_CASE("Test inherited functions from Ninja")
    {
        ariel::Point loc1{1,1};
        ariel::Point loc2{10,10};
        OldNinja tn1{"Trained Ninja 1", loc1};
        OldNinja tn2{"Trained Ninja 2", loc2};
        CHECK(tn1.distance(tn2) == doctest::Approx(12.73).epsilon(0.01));
        tn1.move(&tn2);
        CHECK(tn1.getLocation().distance(loc2) == doctest::Approx(0.73).epsilon(0.01));
        // can slash since 0.73 < 1
        tn1.slash(&tn2);
        CHECK(tn2.getHealth() == (89));
        tn1.hit(30);
        CHECK(tn1.getHealth() == 90);
    }
}
TEST_SUITE("YoungNinja Tests"){
    TEST_CASE("Test constructor and inherited properties from Ninja"){
        ariel::Point loc1{1,1};
        YoungNinja yn1{"Yount Ninja 1", loc1};
        CHECK(yn1.getName() == "Yount Ninja 1");
        CHECK(yn1.getLocation().distance(loc1) == 0);
        CHECK(yn1.isAlive());
        CHECK(yn1.getHealth() == 100);
        CHECK(yn1.getSpeed() == 14);
    }
    
    TEST_CASE("Test inherited functions from Ninja")
    {
        ariel::Point loc1{1,1};
        ariel::Point loc2{10,10};
        YoungNinja yn1{"Yount Ninja 1", loc1};
        YoungNinja yn2{"Yount Ninja 2", loc2};
        CHECK(yn1.distance(yn2) == doctest::Approx(12.73).epsilon(0.01));
        yn1.move(&yn2);
        CHECK(yn1.getLocation().distance(loc2) == 0);
        yn1.move(&yn2); 
        yn1.slash(&yn2);
        CHECK(yn2.getHealth() == 69);
        yn1.hit(30);
        CHECK(yn1.getHealth() == 70);
    }
}
//Team is relevant for all teams as it check there functionality
TEST_SUITE("Team"){
    // MockCharacter* Teamleader= new MockCharacter(Point(0,0),100,"captain hook");
    // Team *t1 ;
    // CHECK_NOTHROW(t1 = new Team(Teamleader));
    // CHECK_NOTHROW(Team(Teamleader));

    // Team *t1 = new Team(Teamleader);
    TEST_CASE("constructor")
    {
        MockCharacter* Teamleader = new MockCharacter(Point(0,0),100,"captain hook");
        Team* t1 = nullptr;
        CHECK_NOTHROW(t1 = new Team(Teamleader));
        delete t1;
        t1 = new Team(Teamleader);
        // because teamleader already in team
        CHECK_THROWS(new Team(Teamleader));
    }
    TEST_CASE("add"){
        Cowboy* Teamleader1 = new Cowboy("captain hook", Point(0,0));
        OldNinja* Teamleader2 = new OldNinja("japanica", Point(0,0));
        MockCharacter* foulty = new MockCharacter(Point(0,0),100,"soldier");
        
        Team* t1 = new Team(Teamleader1);
        Team* t2 = new Team(Teamleader2);

        MockCharacter* member = new MockCharacter(Point(0,0),100,"captain hook");
        // as foulty is not cowboy or ninja
        CHECK_THROWS(t1->add(foulty));
        //already in team
        CHECK_THROWS(t1->add(Teamleader1));
        //already in other team
        CHECK_THROWS(t2->add(Teamleader2));
        // valid
        CHECK_NOTHROW(t1->add(member));
        //already in team
        CHECK_THROWS(t1->add(member));
        //already in other team
        CHECK_THROWS(t2->add(member));
    }

    TEST_CASE("stillalive"){
        MockCharacter* Teamleader1 = new MockCharacter(Point(0,0),100,"captain hook");
        Team* t1 = new Team(Teamleader1);
    }    
}
//Team is relevant for all teams as it check there functionality
TEST_SUITE("Team2"){
    // MockCharacter* Teamleader= new MockCharacter(Point(0,0),100,"captain hook");
    // Team *t1 ;
    // CHECK_NOTHROW(t1 = new Team(Teamleader));
    // CHECK_NOTHROW(Team(Teamleader));

    // Team *t1 = new Team(Teamleader);
    TEST_CASE("constructor")
    {
        MockCharacter* Teamleader = new MockCharacter(Point(0,0),100,"captain hook");
        Team2* t1 = nullptr;
        CHECK_NOTHROW(t1 = new Team2(Teamleader));
        delete t1;
        t1 = new Team2(Teamleader);
        // because teamleader already in team
        CHECK_THROWS(new Team2(Teamleader));
    }
    TEST_CASE("add"){
        Cowboy* Teamleader1 = new Cowboy("captain hook", Point(0,0));
        OldNinja* Teamleader2 = new OldNinja("japanica", Point(0,0));
        MockCharacter* foulty = new MockCharacter(Point(0,0),100,"soldier");
        
        Team2* t1 = new Team2(Teamleader1);
        Team2* t2 = new Team2(Teamleader2);

        MockCharacter* member = new MockCharacter(Point(0,0),100,"captain hook");
        // as foulty is not cowboy or ninja
        CHECK_THROWS(t1->add(foulty));
        //already in team
        CHECK_THROWS(t1->add(Teamleader1));
        //already in other team
        CHECK_THROWS(t2->add(Teamleader2));
        // valid
        CHECK_NOTHROW(t1->add(member));
        //already in team
        CHECK_THROWS(t1->add(member));
        //already in other team
        CHECK_THROWS(t2->add(member));
    }

    TEST_CASE("stillalive"){
        MockCharacter* Teamleader1 = new MockCharacter(Point(0,0),100,"captain hook");
        Team2* t1 = new Team2(Teamleader1);
    }    
}
//special for amosi
TEST_SUITE("'attack' special for amosi"){
    TEST_CASE("team1 agains team1"){
        Cowboy *good = new Cowboy("the good",Point(999,999));
        OldNinja *bad = new OldNinja("the bad",Point(0,0));
        Team* t1 = new Team(good);
        Team* t2 = new Team(bad);
        CHECK_NOTHROW(t1->attack(t2));
        CHECK_NOTHROW(t2->attack(t1));
        while(t1->stillAlive() && t2->stillAlive()){
            t1->attack(t2);
            t2->attack(t1);
        }
        //as t2 is oldNinja that has slow movement and given the distanse t1 should win
        CHECK(t1->stillAlive());
    }
    
    TEST_CASE("team2 agains team2"){
        Cowboy *good = new Cowboy("the good",Point(999,999));
        OldNinja *bad = new OldNinja("the bad",Point(0,0));
        Team2* t1 = new Team2(good);
        Team2* t2 = new Team2(bad);
        CHECK_NOTHROW(t1->attack(t2));
        CHECK_NOTHROW(t2->attack(t1));
        while(t1->stillAlive() && t2->stillAlive()){
            t1->attack(t2);
            t2->attack(t1);
        }
        //as t2 is oldNinja that has slow movement and given the distanse t1 should win
        CHECK(t1->stillAlive());
    }
    // teams can attack another type of team
    TEST_CASE("team2 agains team2"){
        Cowboy *good = new Cowboy("the good",Point(999,999));
        OldNinja *bad = new OldNinja("the bad",Point(0,0));
        Team2* t1 = new Team2(good);
        Team2* t2 = new Team2(bad);
        CHECK_NOTHROW(t1->attack(t2));
        CHECK_NOTHROW(t2->attack(t1));
        while(t1->stillAlive() && t2->stillAlive()){
            t1->attack(t2);
            t2->attack(t1);
        }
        //as t2 is oldNinja that has slow movement and given the distanse t1 should win
        CHECK(t1->stillAlive());
    }
    TEST_CASE("Smart team sould win unde normal condtions"){
        Cowboy *good = new Cowboy("the good",Point(12,12));
        Cowboy *bad = new Cowboy("the bad",Point(0,0));
        
        OldNinja *nin1 = new OldNinja("nin1",Point(1,1));
        OldNinja *nin2 = new OldNinja("nin2",Point(1,1));
        SmartTeam *t1 = new SmartTeam(good);
        Team *t2 = new Team(bad);

        t1->add(nin1);
        t2->add(nin2);
        CHECK_NOTHROW(t1->attack(t2));
        CHECK_NOTHROW(t2->attack(t1));
        while(t1->stillAlive() && t2->stillAlive()){
            t1->attack(t2);
            t2->attack(t1);
        }
        //as t2 is oldNinja that has slow movement and given the distanse t1 should win
        // and make sure smart team not always win
        CHECK(t1->stillAlive());
    }


}