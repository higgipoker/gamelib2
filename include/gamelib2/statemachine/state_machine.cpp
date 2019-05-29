//#include "state_machine.hpp"

// namespace gamelib2 {

////  --------------------------------------------------
////  constructor
////  --------------------------------------------------
// StateMachine::StateMachine()
//  : current_state(nullptr) {
//    inited = false;
//    state_changed = false;
//}

////  --------------------------------------------------
////  destructor
////  --------------------------------------------------
// StateMachine::~StateMachine() {
//    current_state.release();
//}

////  --------------------------------------------------
////  first time initialization
////  --------------------------------------------------
// void StateMachine::init(std::unique_ptr<State> &state) {
//    if (!inited) {
//        current_state = std::move(state);
//        current_state->start();
//        inited = true;
//    }
//}

////  --------------------------------------------------
////  Step
////  --------------------------------------------------
// void StateMachine::update(float dt) {
//    current_state->update(dt);

//    if (current_state->finished()) {
//        current_state->changeToNextState();
//    }
//}

////  --------------------------------------------------
////  change state
////  --------------------------------------------------
// void StateMachine::ChangeState(std::unique_ptr<State> &state) {
//    current_state->end();
//    current_state = std::move(state);
//    current_state->start();
//}

//} // namespace gamelib2
