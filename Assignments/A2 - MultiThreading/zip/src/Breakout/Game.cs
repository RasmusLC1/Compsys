using DIKUArcade;
using DIKUArcade.GUI;
using DIKUArcade.Input;
using System.Collections.Generic;
using DIKUArcade.Events;
using Breakout.BreakoutStates;

namespace Breakout {
public class Game : DIKUGame {
        private StateMachine stateMachine;

        /// <summary>
        /// Initisialises a series of gameevents and sets the statemachine in the window
        /// </summary>
        /// <param name="windowArgs"></param>
        /// <returns></returns>
        public Game (WindowArgs windowArgs) : base(windowArgs) {
            BreakoutBus.GetBus().InitializeEventBus(new List<GameEventType> { 
                GameEventType.InputEvent, 
                GameEventType.WindowEvent, 
                GameEventType.GameStateEvent, 
                GameEventType.GraphicsEvent,
                GameEventType.PlayerEvent});
            window.SetKeyEventHandler(KeyHandler);
            stateMachine = new StateMachine(window);
        } 

        /// <summary>
        /// Determines the keyboard input and sends out a message depending on the input
        /// </summary>
        /// <param name="action">The given keyboard action</param>
        /// <param name="key">The keyboard key</param>
        private void KeyHandler(KeyboardAction action, KeyboardKey key) {
            if (action == KeyboardAction.KeyPress) {
                switch(key) {
                    case (KeyboardKey.A):
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.InputEvent,
                            Message = "MOVE_LEFT"});
                        break;
                    case (KeyboardKey.D):
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.InputEvent,
                            Message = "MOVE_RIGHT"});
                        break;
                    case (KeyboardKey.W):
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.InputEvent,
                            Message = "MOVE_UP"});
                        break;
                    case (KeyboardKey.S):
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.InputEvent,
                            Message = "MOVE_DOWN"});
                        break;
                    default:
                        break;
                }
            } else if (action == KeyboardAction.KeyRelease) {
                switch(key){
                    case (KeyboardKey.A):
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.InputEvent,
                            Message = "STOP_MOVE_LEFT"});
                        break;
                    case (KeyboardKey.D):
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.InputEvent,
                            Message = "STOP_MOVE_RIGHT"});
                        break;
                    case (KeyboardKey.Escape):
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.InputEvent,
                            Message = "CLOSE_WINDOW"});
                            break;
                    case (KeyboardKey.Enter):
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.InputEvent,
                            Message = "ENTER"});
                            break;
                    default:
                        break;
                }
            }
        }
         
        /// <summary>
        /// Renders all objects
        /// </summary>
        public override void Render() {
            stateMachine.Render();
        }

        /// <summary>
        /// Updates the game
        /// </summary>
        public override void Update() {
            window.PollEvents();
            BreakoutBus.GetBus().ProcessEventsSequentially();
            stateMachine.Update();
        }
    }
}