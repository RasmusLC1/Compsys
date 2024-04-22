using System.IO;
using System.Collections.Generic;
using DIKUArcade.State;
using DIKUArcade.Entities;
using DIKUArcade.Graphics;
using DIKUArcade.Input;
using DIKUArcade.Math;
using DIKUArcade.Events;
using Breakout.Levels;

namespace Breakout.BreakoutStates {
    public class LevelMenu : IGameState {
        private static LevelMenu instance = null;
        private Entity backGroundImage;
        private Text[] menuButtons;
        private LevelDictionary LevelNames = new LevelDictionary();
        public Dictionary<int, string> leveldata = new Dictionary<int, string>();
        private int activeMenuButton;
        private int maxMenuButtons;
        private string CurrentLevel;

        /// <summary>
        /// Gets the level chosen.
        /// </summary>
        public string GetCurrentLevel {
            get {return CurrentLevel;}
        }

        /// <summary>
        /// Creates the background image for the menu and sets the menu texts
        /// </summary>
        public LevelMenu () {
            leveldata = LevelNames.GetFileNames();
            backGroundImage = new Entity (
                new StationaryShape (new Vec2F (0.0f,0.0f), new Vec2F (1.0f,1.0f)), 
                new Image (Path.Combine("Assets", "Images", "BreakoutTitleScreen.png")));
            menuButtons = new[] {
                new Text ("Back", new Vec2F (0.45f,0.1f), new Vec2F (0.3f,0.3f)),
                new Text (leveldata[0], new Vec2F (0.65f,0.3f), new Vec2F (0.2f,0.2f)),
                new Text (leveldata[1], new Vec2F (0.65f,0.4f), new Vec2F (0.2f,0.2f)),
                new Text (leveldata[5], new Vec2F (0.65f,0.5f), new Vec2F (0.2f,0.2f)),
                new Text (leveldata[4], new Vec2F (0.25f,0.3f), new Vec2F (0.2f,0.2f)),
                new Text (leveldata[3], new Vec2F (0.25f,0.4f), new Vec2F (0.2f,0.2f)),
                new Text (leveldata[2], new Vec2F (0.25f,0.5f), new Vec2F (0.2f,0.2f))};
            activeMenuButton = 0;
            maxMenuButtons = menuButtons.Length;
            UpdateButton();
            foreach (Text text in menuButtons) {
                text.SetColor(System.Drawing.Color.DeepSkyBlue);
                text.SetFont("Comic Sans");
            } 
        }

        /// <summary>
        /// Creates an instance of LevelMenu if null, otherwise returns the instance
        /// </summary>
        /// <returns>An instance of LevelMenu</returns>
        public static LevelMenu GetInstance() {
            if (LevelMenu.instance == null) {
                LevelMenu.instance = new LevelMenu();
            }
            return LevelMenu.instance;
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
                        if (menuButtons[activeMenuButton] == menuButtons[4] ) {
                            activeMenuButton = 0;
                        } else if (menuButtons[activeMenuButton] != menuButtons[0]) {
                            activeMenuButton -= 1;
                        }
                        break;
                    case KeyboardKey.W:
                        if (menuButtons[activeMenuButton] != menuButtons[menuButtons.Length-1]) {
                            activeMenuButton += 1;
                        }
                        break;
                    case KeyboardKey.A:
                        if (activeMenuButton + 3 > 3 && activeMenuButton + 3 < 7) {
                            activeMenuButton += 3;
                        }
                        break;
                    case KeyboardKey.D:
                        if (activeMenuButton - 3 > 0 && activeMenuButton - 3 < 4) {
                            activeMenuButton -= 3;
                        }
                        break;
                    case KeyboardKey.Enter:
                        if (activeMenuButton == 0) {
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "MAIN_MENU"});
                        } else if (activeMenuButton == 1) {
                            CurrentLevel = leveldata[0];
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "GAME_RUNNING",});
                        }  else if (activeMenuButton == 2) {
                            CurrentLevel = leveldata[1];
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "GAME_RUNNING",});
                        } else if (activeMenuButton == 3) {
                            CurrentLevel = leveldata[5];
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "GAME_RUNNING",});
                        } else if (activeMenuButton == 4) {
                            CurrentLevel = leveldata[4];
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "GAME_RUNNING",});
                        } else if (activeMenuButton == 5) {
                            CurrentLevel = leveldata[3];
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "GAME_RUNNING",});
                        } else if (activeMenuButton == 6) {
                            CurrentLevel = leveldata[2];
                            BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "GAME_RUNNING",});
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
        /// Renders the LevelMenu objects
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