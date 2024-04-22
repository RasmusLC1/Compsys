using DIKUArcade.State;
using DIKUArcade.Entities;
using DIKUArcade.Input;
using DIKUArcade.Math;
using System.Collections.Generic;
using DIKUArcade.Events;
using System;
using Breakout.Levels;
using Breakout.Gameinfo;
using Breakout.Factories;
using Breakout.EntityData.EntityLogic;

namespace Breakout.BreakoutStates {
    public class GameRunning : IGameState {
        private static GameRunning instance = null;
        private GameValues values = GameValues.GetInstance();
        private CentralFactory factory= new CentralFactory();
        private EntityContainer <Ball> balls = new EntityContainer <Ball> ();
        private Dictionary<int, string> leveldata = new Dictionary <int, string> ();
        private Player player;
        private GameChecker gamechecker = new GameChecker();
        private Logic logic = new Logic ();
        private Random rand = new Random();
        private LevelDictionary LevelNames = new LevelDictionary();
        private LevelBuilder levelBuilder = LevelBuilder.GetInstance ();
        public Player GetPlayer {
            get {return player;}
        }
        public EntityContainer<Ball> GetBalls {
            get {return balls;}
        }
        public void AddBalls(Ball ball) {
            balls.AddEntity(ball);
        }

        /// <summary>
        /// Initialises the game with the various entities and animation needed for the game
        /// </summary>
        private void InitializeGameState () {
            leveldata = LevelNames.GetFileNames();
            balls.ClearContainer();
            player = (Player)(factory.Build(new Vec2F(0.45f, 0.05f), "Player"));
            values.initializeNumber(LevelMenu.GetInstance().GetCurrentLevel);
            AddBalls((Ball)(factory.Build(new Vec2F(0.45f, 0.05f), "Ball")));
            levelBuilder.LevelCreator(LevelMenu.GetInstance().GetCurrentLevel);
        }

        /// <summary>
        /// Sets the GameRunning to the current instance
        /// </summary>
        /// <returns>GameRunning instance</returns>
        public static GameRunning GetInstance() {
            if (GameRunning.instance == null) {
                GameRunning.instance = new GameRunning();
            }
            return GameRunning.instance;
        }

        /// <summary>
        /// Handles certain events from a given keyboard key
        /// </summary>
        /// <param name="action">The given keyboard action</param>
        /// <param name="key">The keyboard key</param>
        public void HandleKeyEvent(KeyboardAction action, KeyboardKey key) {
           if (action == KeyboardAction.KeyPress) {
                switch (key) {
                    case KeyboardKey.D:
                        player.SetMoveRight(true);
                        break;  
                    case KeyboardKey.A:
                        player.SetMoveLeft(true);
                        break;
                    case KeyboardKey.Escape:
                        BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                                EventType = GameEventType.GameStateEvent,
                                Message = "CHANGE_STATE",
                                StringArg1 = "GAME_PAUSED"});
                        break;
                    default:
                        break;
                }
            } else if (action == KeyboardAction.KeyRelease) {
                switch (key) {
                    case KeyboardKey.D:
                        player.SetMoveRight(false);
                        break;
                    case KeyboardKey.A:
                        player.SetMoveLeft(false);
                        break;
                    default:
                        break;
                }
            }
        }

        /// <summary>
        /// Checks the current GameState based on gamechecker and the count of blocks
        /// </summary>
        public void Gamestate () {
            values.UpdateTimer();
            if(levelBuilder.GetBlocks.CountEntities() == 0) {
                string level = leveldata[rand.Next(0, leveldata.Count)];
                levelBuilder.LevelCreator(level);
                player.ResetPosition();
                balls.ClearContainer();
                AddBalls((Ball)(factory.Build(new Vec2F(player.Shape.Position.X, player.Shape.Position.Y+0.05f), "Ball")));
            }
            if (gamechecker.GameOver(values.GetLives, values.GetTime, balls.CountEntities()) == 2) {
                player.ResetPosition();
                values.DecreaseLives();
                AddBalls((Ball)(factory.Build(new Vec2F(player.Shape.Position.X, player.Shape.Position.Y+0.05f), "Ball")));
            } else if (gamechecker.GameOver(values.GetLives, values.GetTime, balls.CountEntities()) == 0 ) {
                BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.GameStateEvent,
                            Message = "CHANGE_STATE",
                            StringArg1 = "GAMELOST"});
            }
            if (values.GetScore >= 200) {
                BreakoutBus.GetBus().RegisterEvent(new GameEvent {
                            EventType = GameEventType.GameStateEvent,
                            Message = "CHANGE_STATE",
                            StringArg1 = "GAMEWON"});    
            }
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }

        /// <summary>
        /// Renders the GameRunning state
        /// </summary>
        public void RenderState() {
            player.RenderEntity();
            balls.RenderEntities();
            levelBuilder.Render();
            values.Render();
        }

        /// <summary>
        /// Updates the GameRunning state
        /// </summary>
        public void UpdateState() {
            logic.EntityLogic(levelBuilder.GetBlocks, balls, levelBuilder.GetPowerUps, player);
            Gamestate();
        }
        
        /// <summary>
        /// resets the state
        /// </summary>
        public void ResetState() {
            GameRunning.instance.InitializeGameState();
        }
    }
}