using System.IO;
using System.Collections.Generic;
using DIKUArcade.State;
using DIKUArcade.Entities;
using DIKUArcade.Graphics;
using DIKUArcade.Input;
using DIKUArcade.Math;
using DIKUArcade.Events;
using Breakout.Gameinfo;
using Breakout.Levels;

namespace Breakout.BreakoutStates {
    public class GameLost : IGameState {
        private static GameLost instance = null;
        private Entity backGroundImage;
        private Dictionary<int, string> levelData = new Dictionary<int, string>();
        private LevelDictionary levelNames = new LevelDictionary();
        private GameValues values = GameValues.GetInstance();
        private Text[] menuButtons;
        private int activeMenuButton;
        private int maxMenuButtons;
        private Text score;

        /// <summary>
        /// Creates the background image for the menu and sets the menu texts
        /// </summary>
        public GameLost () {
            levelData = levelNames.GetFileNames();
            backGroundImage = new Entity (
                new StationaryShape (new Vec2F (0.0f,0.0f), new Vec2F (1.0f,1.0f)), 
                new Image (Path.Combine("Assets", "Images", "BreakoutTitleScreen.png")));
            menuButtons = new[] {
                new Text ("Quit", new Vec2F (0.4f,0.10f), new Vec2F (0.3f,0.3f)),
                new Text ("Main Menu", new Vec2F(0.4f, 0.25f), new Vec2F (0.3f, 0.3f)),
                new Text ("Try again", new Vec2F(0.4f, 0.35f), new Vec2F (0.3f, 0.3f))};
            activeMenuButton = 0;
            score = new Text ("Score: "+values.GetScore.ToString(), new Vec2F(0.4f, 0.45f), new Vec2F (0.3f, 0.3f));
            score.SetColor(System.Drawing.Color.Yellow);
            maxMenuButtons = menuButtons.Length;
            UpdateButton();
            foreach (Text text in menuButtons) {
                text.SetColor(System.Drawing.Color.DeepSkyBlue);
                text.SetFont("Comic Sans");
            }
        }

        /// <summary>
        /// Creates an instance of GameLost if null, otherwise returns the instance
        /// </summary>
        /// <returns>An instance of GameLost</returns>
        public static GameLost GetInstance() {
            if (GameLost.instance == null) {
                GameLost.instance = new GameLost();
            }
            return GameLost.instance;
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
        public void HandleKeyEvent (KeyboardAction action, KeyboardKey key) {
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
                        if (activeMenuButton == 0) {
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.WindowEvent,
                                Message = "QUIT"});
                        } else if (activeMenuButton == 1) {
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "MAIN_MENU",});
                        }  else if (activeMenuButton == 2) {
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "LEVEL_MENU",});
                        }
                        break;
                    case KeyboardKey.Escape:
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "MAIN_MENU",});
                        break;
                    default:
                        break;
                }
            }
            UpdateButton();
        }
        
        /// <summary>
        /// Renders the GameLost objects
        /// </summary>
        public void RenderState() {
            backGroundImage.RenderEntity();
            foreach (Text text in menuButtons) {
                text.RenderText();
            }
            score.RenderText();
        }

        public void UpdateState() {}
        public void ResetState() {}
    }
}