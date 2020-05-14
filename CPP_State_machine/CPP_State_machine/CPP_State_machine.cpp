#include <iostream>
#include <tuple>
#include <variant>
#include <functional>

template <typename... States>
class StateMachine
{
private:
    std::tuple<States...> states;
    std::variant<States *...> currentState{ &std::get<0>(states) };

public:
    template <typename State>
    void transitionTo()
    {
        currentState = &std::get<State>(states);
    }

    template <typename Event>
    void handle(const Event& event)
    {
        auto passEventToState = [this, &event](auto statePtr) {
            statePtr->handle(event).execute(*this);
        };
        std::visit(passEventToState, currentState);
    }

};

template <typename State>
struct TransitionTo
{
    template <typename Machine>
    void execute(Machine& machine)
    {
        machine.template transitionTo<State>();
    }
};

struct Nothing
{
    template <typename Machine>
    void execute(Machine&)
    {
    }
};

struct turn_off
{
};
struct turn_on {

};
struct passed {

};
struct failure
{
};
struct service
{
};
struct cancel {

};
struct card_inserted {

};
struct read_card {

};
struct eject_card {

};


struct Off_state;
struct Self_Test_state;
struct Idle_state;
struct Maintenance_state;
struct Out_of_Service_state;
struct Serving_Customer_state;
struct Customer_Authentication_state;
struct Selecting_Transaction_state;
struct Transaction_state;


struct Off_state
{
    TransitionTo<Self_Test_state> handle(const turn_on&) const
    {
        std::cout << "Go to Self_Test state!" << std::endl;
        return {};
    }

    Nothing handle(const turn_off&) const
    {
        std::cout << "Cannot turn off. ATM is already shut down!" << std::endl;
        return {};
    }
    Nothing handle(const failure&) const
    {
        std::cout << "Cannot perform step \"failure\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const passed&) const
    {
        std::cout << "Cannot perform step \"passed\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const service&) const
    {
        std::cout << "Cannot perform step \"service\" in this state!" << std::endl;
        return {};

    }
    Nothing handle(const cancel&) const
    {
        std::cout << "Cannot perform step \"cancel\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const card_inserted&) const
    {
        std::cout << "Cannot perform step \"card_inserted\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const read_card&) const
    {
        std::cout << "Cannot perform step \"read_card\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const eject_card&) const
    {
        std::cout << "Cannot perform step \"eject_card\" in this state!" << std::endl;
        return {};
    }
};

struct Self_Test_state
{
    Nothing handle(const turn_on&) const
    {
        std::cout << "Cannot turn on. ATM is already running!" << std::endl;
        return {};
    }

    Nothing handle(const turn_off&) const
    {
        std::cout << "Cannot turn off. ATM is already shut down!" << std::endl;
        return {};
    }
    TransitionTo<Out_of_Service_state> handle(const failure&) const
    {
        std::cout << "Go to Out_of_Serviced state" << std::endl;
        return {};
    }
    TransitionTo<Idle_state> handle(const passed&) const
    {
        std::cout << "Go to Idle state" << std::endl;
        return {};
    }
    Nothing handle(const service&) const
    {
        std::cout << "Cannot perform step \"service\" in this state!" << std::endl;
        return {};

    }
    Nothing handle(const cancel&) const
    {
        std::cout << "Cannot perform step \"cancel\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const card_inserted&) const
    {
        std::cout << "Cannot perform step \"card_inserted\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const read_card&) const
    {
        std::cout << "Cannot perform step \"read_card\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const eject_card&) const
    {
        std::cout << "Cannot perform step \"eject_card\" in this state!" << std::endl;
        return {};
    }
};

struct Idle_state
{
    Nothing handle(const turn_on&) const
    {
        std::cout << "Cannot turn on. ATM is already running!" << std::endl;
        return {};
    }

    TransitionTo<Off_state> handle(const turn_off&) const
    {
        std::cout << "Go to turn_off state!" << std::endl;
        return {};
    }
    Nothing handle(const failure&) const
    {
        std::cout << "Cannot perform step \"failure\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const passed&) const
    {
        std::cout << "Cannot perform step \"passed\" in this state!" << std::endl;
        return {};
    }
    TransitionTo<Maintenance_state> handle(const service&) const
    {
        std::cout << "Go to Maintenance state!" << std::endl;
        return {};

    }
    Nothing handle(const cancel&) const
    {
        std::cout << "Cannot perform step \"cancel\" in this state!" << std::endl;
        return {};
    }
    TransitionTo<Serving_Customer_state> handle(const card_inserted&) const
    {
        std::cout << "Go to Serving_Customer state!" << std::endl;
        return {};
    }
    Nothing handle(const read_card&) const
    {
        std::cout << "Cannot perform step \"read_card\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const eject_card&) const
    {
        std::cout << "Cannot perform step \"eject_card\" in this state!" << std::endl;
        return {};
    }
};

struct Maintenance_state
{
    Nothing handle(const turn_on&) const
    {
        std::cout << "Cannot turn on. ATM is already running!" << std::endl;
        return {};
    }

    Nothing handle(const turn_off&) const
    {
        std::cout << "Cannot turn off. ATM is already shut down!" << std::endl;
        return {};
    }
    TransitionTo<Out_of_Service_state> handle(const failure&) const
    {
        std::cout << "Go to Out_of_Service state!" << std::endl;
        return {};
    }
    TransitionTo<Self_Test_state> handle(const passed&) const
    {
        std::cout << "Go to Self_Test state!" << std::endl;
        return {};
    }
    Nothing handle(const service&) const
    {
        std::cout << "Cannot perform step \"service\" in this state!" << std::endl;
        return {};

    }
    Nothing handle(const cancel&) const
    {
        std::cout << "Cannot perform step \"cancel\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const card_inserted&) const
    {
        std::cout << "Cannot perform step \"card_inserted\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const read_card&) const
    {
        std::cout << "Cannot perform step \"read_card\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const eject_card&) const
    {
        std::cout << "Cannot perform step \"eject_card\" in this state!" << std::endl;
        return {};
    }
};

struct Out_of_Service_state
{
    Nothing handle(const turn_on&) const
    {
        std::cout << "Cannot turn on. ATM is already running!" << std::endl;
        return {};
    }

    TransitionTo<Off_state> handle(const turn_off&) const
    {
        std::cout << "Go to Off state!" << std::endl;
        return {};
    }
    Nothing handle(const failure&) const
    {
        std::cout << "Cannot perform step \"failure\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const passed&) const
    {
        std::cout << "Cannot perform step \"passed\" in this state!" << std::endl;
        return {};
    }
    TransitionTo<Maintenance_state> handle(const service&) const
    {
        std::cout << "Go to Maintenance state!" << std::endl;
        return {};

    }
    Nothing handle(const cancel&) const
    {
        std::cout << "Cannot perform step \"cancel\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const card_inserted&) const
    {
        std::cout << "Cannot perform step \"card_inserted\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const read_card&) const
    {
        std::cout << "Cannot perform step \"read_card\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const eject_card&) const
    {
        std::cout << "Cannot perform step \"eject_card\" in this state!" << std::endl;
        return {};
    }
};

//-------------------------------------
struct Serving_Customer_state
{
    Nothing handle(const turn_on&) const
    {
        std::cout << "Cannot turn on. ATM is already running!" << std::endl;
        return {};
    }

    Nothing handle(const turn_off&) const
    {
        std::cout << "Cannot turn off. ATM is already shut down!" << std::endl;
        return {};
    }
    TransitionTo<Out_of_Service_state> handle(const failure&) const
    {
        std::cout << "Go to Out_of_service state!" << std::endl;
        return {};
    }
    TransitionTo<Idle_state> handle(const passed&) const
    {
        std::cout << "GO to Idle state!" << std::endl;
        return {};
    }
    Nothing handle(const service&) const
    {
        std::cout << "Cannot perform step \"service\" in this state!" << std::endl;
        return {};

    }
    TransitionTo<Idle_state> handle(const cancel&) const
    {
        std::cout << "Go to Idle state!" << std::endl;
        return {};
    }
    Nothing handle(const card_inserted&) const
    {
        std::cout << "Cannot perform step \"card_inserted\" in this state!" << std::endl;
        return {};
    }
    TransitionTo<Customer_Authentication_state> handle(const read_card&) const
    {
        std::cout << "Go to Customer_Authentication state!" << std::endl;
        return {};
    }
    TransitionTo<Idle_state> handle(const eject_card&) const
    {
        std::cout << "Go to Idle state!" << std::endl;
        return {};
    }
};

struct Customer_Authentication_state
{
    Nothing handle(const turn_on&) const
    {
        std::cout << "Cannot turn on. ATM is already running!" << std::endl;
        return {};
    }

    Nothing handle(const turn_off&) const
    {
        std::cout << "Cannot turn off. ATM is already shut down!" << std::endl;
        return {};
    }
    Nothing handle(const failure&) const
    {
        std::cout << "Cannot perform step \"failure\" in this state!" << std::endl;
        return {};
    }
    TransitionTo<Selecting_Transaction_state> handle(const passed&) const
    {
        std::cout << "Go to Selecting_Transaction state!" << std::endl;
        return {};
    }
    Nothing handle(const service&) const
    {
        std::cout << "Cannot perform step \"service\" in this state!" << std::endl;
        return {};

    }
    Nothing handle(const cancel&) const
    {
        std::cout << "Cannot perform step \"cancel\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const card_inserted&) const
    {
        std::cout << "Cannot perform step \"card_inserted\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const read_card&) const
    {
        std::cout << "Cannot perform step \"read_card\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const eject_card&) const
    {
        std::cout << "Cannot perform step \"eject_card\" in this state!" << std::endl;
        return {};
    }
    
};

struct Selecting_Transaction_state
{
    Nothing handle(const turn_on&) const
    {
        std::cout << "Cannot turn on. ATM is already running!" << std::endl;
        return {};
    }

    Nothing handle(const turn_off&) const
    {
        std::cout << "Cannot turn off. ATM is already shut down!" << std::endl;
        return {};
    }
    Nothing handle(const failure&) const
    {
        std::cout << "Cannot perform step \"failure\" in this state!" << std::endl;
        return {};
    }
    TransitionTo<Transaction_state> handle(const passed&) const
    {
        std::cout << "Go to Transaction state!" << std::endl;
        return {};
    }
    Nothing handle(const service&) const
    {
        std::cout << "Cannot perform step \"service\" in this state!" << std::endl;
        return {};

    }
    Nothing handle(const cancel&) const
    {
        std::cout << "Cannot perform step \"cancel\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const card_inserted&) const
    {
        std::cout << "Cannot perform step \"card_inserted\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const read_card&) const
    {
        std::cout << "Cannot perform step \"read_card\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const eject_card&) const
    {
        std::cout << "Cannot perform step \"eject_card\" in this state!" << std::endl;
        return {};
    }
};

struct Transaction_state
{
    Nothing handle(const turn_on&) const
    {
        std::cout << "Cannot turn on. ATM is already running!" << std::endl;
        return {};
    }

    Nothing handle(const turn_off&) const
    {
        std::cout << "Cannot turn off. ATM is already shut down!" << std::endl;
        return {};
    }
    Nothing handle(const failure&) const
    {
        std::cout << "Cannot perform step \"failure\" in this state!" << std::endl;
        return {};
    }
    TransitionTo<Serving_Customer_state> handle(const passed&) const
    {
        std::cout << "Go to Serving_Customer state!" << std::endl;
        return {};
    }
    Nothing handle(const service&) const
    {
        std::cout << "Cannot perform step \"service\" in this state!" << std::endl;
        return {};

    }
    Nothing handle(const cancel&) const
    {
        std::cout << "Cannot perform step \"cancel\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const card_inserted&) const
    {
        std::cout << "Cannot perform step \"card_inserted\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const read_card&) const
    {
        std::cout << "Cannot perform step \"read_card\" in this state!" << std::endl;
        return {};
    }
    Nothing handle(const eject_card&) const
    {
        std::cout << "Cannot perform step \"eject_card\" in this state!" << std::endl;
        return {};
    }
};


using ATM = StateMachine<Off_state, Self_Test_state, Idle_state, Maintenance_state, Out_of_Service_state, Out_of_Service_state, 
                        Serving_Customer_state, Customer_Authentication_state, Selecting_Transaction_state, Transaction_state >;

int main()
{
    ATM bank_1;

    bank_1.handle(turn_off{});
    bank_1.handle(turn_on{});
    bank_1.handle(passed{});
   // bank_1.handle(service{});
   // bank_1.handle(failure{});
  /*  bank_1.handle(service{});
    bank_1.handle(passed{});
    bank_1.handle(passed{});*/
    bank_1.handle(card_inserted{});

    bank_1.handle(read_card{});
    bank_1.handle(passed{});
    bank_1.handle(passed{});
    bank_1.handle(passed{});
    bank_1.handle(eject_card{});
    //bank_1.handle(cancel{});
    bank_1.handle(turn_off{});






    return 0;
}