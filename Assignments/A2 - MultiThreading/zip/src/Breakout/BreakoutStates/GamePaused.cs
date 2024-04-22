using DIKUArcade.State;
using DIKUArcade.Entities;
using DIKUArcade.Graphics;
using DIKUArcade.Input;
using System.IO;
using DIKUArcade.Math;
using DIKUArcade.Events;

namespace Breakout.BreakoutStates {
    public class GamePaused : IGameState {
        private static GamePaused instance = null;
        private Entity backGroundImage;
        private Text[] menuButtons;
        private int activeMenuButton;
        private int maxMenuButtons;

        /// <summary>
        /// Creates the background image for the menu and sets the menu texts
        /// </summary>
        public GamePaused() {
            backGroundImage = new Entity (
                new StationaryShape (new Vec2F (0.0f,0.0f), new Vec2F (1.0f,1.0f)), 
                new Image (Path.Combine("Assets", "Images", "BreakoutTitleScreen.png")));
            menuButtons = new[] {
                new Text ("Main Menu", new Vec2F (0.4f,0.1f), new Vec2F (0.3f,0.3f)),
                new Text ("Resume", new Vec2F (0.4f,0.2f), new Vec2F (0.3f,0.3f))};
            activeMenuButton = 0;
            maxMenuButtons = menuButtons.Length;
            UpdateButton();
            foreach (Text text in menuButtons) {
                text.SetColor(System.Drawing.Color.DeepSkyBlue);
                text.SetFont("Comic Sans");
            }
        }

        /// <summary>
        /// Creates an instance of GamePaused if null, otherwise returns the instance
        /// </summary>
        /// <returns>An instance of GamePaused</returns>
        public static GamePaused GetInstance() {
            if (GamePaused.instance == null) {
                GamePaused.instance = new GamePaused();
            }
            return GamePaused.instance;
        }

        /// <summary>
        /// Updates the menu text dependent on where the button is located
        /// </summary>
        private void UpdateButton() {
            foreach (Text button in menuButtons) {
                if (button == menuButtons[activeMenuButton]) {
                    button.SetColor(System.Drawing.Color.White);
                }
                else {
                    button.SetColor(System.Drawing.Color.DeepSkyBlue);
                }
            }
        }

        /// <summary>
        /// Handles certain events from a given keyboard key. If entered,
        /// it sends out a message depending on button location
        /// </summary>
        /// <param name="action">The given keyboard action</param>
        /// <param name="key">The keyboard key</param>
        public void HandleKeyEvent(KeyboardAction action, KeyboardKey key) {
            if (action == KeyboardAction.KeyPress) {
                switch (key) {
                    case KeyboardKey.S:  
                        if (menuButtons[activeMenuButton] != menuButtons[0]) {
                            activeMenuButton -= 1;
                        }
                        break;
                    case KeyboardKey.W:
                        if (menuButtons[activeMenuButton] != menuButtons[menuButtons.Length-1]) {
                            activeMenuButton += 1;
                        }
                        break;
                    case KeyboardKey.Enter:
                        if (activeMenuButton == 1) {
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "GAME_RUNNING"});
                        } else if (activeMenuButton == 0) {
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "MAIN_MENU"});
                        }
                        break;
                    case KeyboardKey.Escape:
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.GameStateEvent,
                            Message = "CHANGE_STATE",
                            StringArg1 = "MAIN_MENU"});
                            break;
                    default:
                        break;
                }
            }
            UpdateButton();
        }

        /// <summary>
        /// Renders the GamePaused objects
        /// </summary>
        public void RenderState() {
            backGroundImage.RenderEntity();
            foreach (Text text in menuButtons) {
                text.RenderText();
            }
        }
        
        public void ResetState() {}
        public void UpdateState() {}
    }
}