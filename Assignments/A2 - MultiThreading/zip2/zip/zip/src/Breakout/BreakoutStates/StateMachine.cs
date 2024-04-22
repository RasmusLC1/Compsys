using DIKUArcade.Events;
using DIKUArcade.State;
using DIKUArcade.GUI;
using DIKUArcade.Input;

namespace Breakout.BreakoutStates {
    public class StateMachine : IGameEventProcessor {
        private Window Gamewindow;
        public IGameState ActiveState {get; private set;}

        /// <summary>
        /// Subscribes the various GameEventTypes to the eventbus
        /// </summary>
        /// <param name="window">The current window that is active</param>
        public StateMachine(Window window) {
            Gamewindow = window;
            BreakoutBus.GetBus().Subscribe(GameEventType.GameStateEvent, this);
            BreakoutBus.GetBus().Subscribe(GameEventType.InputEvent, this);
            BreakoutBus.GetBus().Subscribe(GameEventType.WindowEvent, this);
            ActiveState = MainMenu.GetInstance();
        }

        /// <summary>
        /// Switches the active state to the given statetype
        /// </summary>
        /// <param name="stateType"> The GameStateType you wish to switch to </param>
        private void SwitchState(GameStateType stateType) {
            switch (stateType) {
                case (GameStateType.MainMenu):
                    ActiveState = MainMenu.GetInstance();
                    break;
                case (GameStateType.GameRunning):
                    if (ActiveState != GamePaused.GetInstance()) {
                        GameRunning.GetInstance().ResetState();
                    }
                    ActiveState = GameRunning.GetInstance();
                    break;
                case (GameStateType.LevelMenu):
                    ActiveState = LevelMenu.GetInstance();
                    break;
                case (GameStateType.GamePaused):
                    ActiveState = GamePaused.GetInstance();
                    break;
                case (GameStateType.GameLost):
                    ActiveState = GameLost.GetInstance();
                    break;
                case (GameStateType.GameWon):
                    ActiveState = GameWon.GetInstance();
                    break;
                default:
                    throw new System.ArgumentException("GameStateType not recognised");
            }
        }

        /// <summary>
        /// Processes events based on the Gameeventtype to change the events message 
        /// </summary>
        /// <param name="gameEvent"> the gameevent</param>
        public void ProcessEvent (GameEvent gameEvent) {
            if (gameEvent.EventType == GameEventType.GameStateEvent) {
                if (gameEvent.Message == "CHANGE_STATE") {                   
                    SwitchState(StateTransformer.TransformStringToState(gameEvent.StringArg1));
                }
            }
            else if (gameEvent.EventType == GameEventType.WindowEvent) {
                if (gameEvent.Message == "QUIT") {
                    Gamewindow.CloseWindow();
                }
            }
            else if (gameEvent.EventType == GameEventType.InputEvent) {
                switch (gameEvent.Message) {
                    case "MOVE_LEFT":
                        ActiveState.HandleKeyEvent(KeyboardAction.KeyPress, KeyboardKey.A);
                        break;
                    case "MOVE_RIGHT":
                        ActiveState.HandleKeyEvent(KeyboardAction.KeyPress,KeyboardKey.D);
                        break;
                    case "MOVE_UP":
                        ActiveState.HandleKeyEvent(KeyboardAction.KeyPress, KeyboardKey.W);
                        break;
                    case "MOVE_DOWN":
                        ActiveState.HandleKeyEvent(KeyboardAction.KeyPress, KeyboardKey.S);
                        break;
                    case "CLOSE_WINDOW":
                        ActiveState.HandleKeyEvent(KeyboardAction.KeyPress, KeyboardKey.Escape);
                        break;
                    case "ENTER":
                        ActiveState.HandleKeyEvent(KeyboardAction.KeyPress, KeyboardKey.Enter);
                        break;
                    case "STOP_MOVE_LEFT":
                        ActiveState.HandleKeyEvent(KeyboardAction.KeyRelease, KeyboardKey.A);
                        break;
                    case "STOP_MOVE_RIGHT":
                        ActiveState.HandleKeyEvent(KeyboardAction.KeyRelease, KeyboardKey.D);
                        break;
                    default: 
                        break;
                }
            } 
        }

        /// <summary>
        /// Renders the current active state
        /// </summary>
        public void Render() {
            ActiveState.RenderState();
        }
        
        /// <summary>
        /// updates the current active state
        /// </summary>
        public void Update() {
            ActiveState.UpdateState();
        }        
    }
}