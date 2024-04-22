using DIKUArcade.State;
using DIKUArcade.Entities;
using DIKUArcade.Graphics;
using DIKUArcade.Input;
using System.IO;
using DIKUArcade.Math;
using DIKUArcade.Events;
using Breakout.Gameinfo;

namespace Breakout.BreakoutStates {
    public class GameWon : IGameState {
        private static GameWon instance = null;
        private GameValues values = GameValues.GetInstance();
        private Entity backGroundImage;
        private Text[] menuButtons;
        private int activeMenuButton;
        private int maxMenuButtons;
        private Text score;

        /// <summary>
        /// Creates the background image for the menu and sets the menu texts
        /// </summary>
        public GameWon() {
            backGroundImage = new Entity (
                new StationaryShape (new Vec2F (0.0f,0.0f), new Vec2F (1.0f,1.0f)), 
                new Image (Path.Combine("Assets", "Images", "BreakoutTitleScreen.png")));
            menuButtons = new[] {
                new Text ("Main Menu", new Vec2F (0.4f,0.1f), new Vec2F (0.3f,0.3f)),
                new Text ("Try Again", new Vec2F (0.4f,0.2f), new Vec2F (0.3f,0.3f)),
                new Text ("Victory", new Vec2F (0.4f,0.3f), new Vec2F (0.5f,0.5f)),};
            activeMenuButton = 0;
            maxMenuButtons = menuButtons.Length;
            UpdateButton();
            score = new Text ("Score: "+values.GetScore.ToString(), new Vec2F(0.4f, 0.45f), new Vec2F (0.3f, 0.3f));
            score.SetColor(System.Drawing.Color.Yellow);
            foreach (Text text in menuButtons) {
                text.SetColor(System.Drawing.Color.DeepSkyBlue);
                text.SetFont("Comic Sans");
            }
        }

        /// <summary>
        /// Creates an instance of GamePaused if null, otherwise returns the instance
        /// </summary>
        /// <returns>An instance of GamePaused</returns>
        public static GameWon GetInstance() {
            if (GameWon.instance == null) {
                GameWon.instance = new GameWon();
            }
            return GameWon.instance;
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
                                StringArg1 = "LEVEL_MENU"}); 
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
            score.RenderText();
        }
        
        public void ResetState() {}
        public void UpdateState() {}
    }
}