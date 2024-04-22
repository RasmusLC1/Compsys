using DIKUArcade.Math;
using DIKUArcade.Entities;
using DIKUArcade.Graphics;

namespace Breakout.Gameinfo {
    public class GameValues {
        private static GameValues instance = null;
        private Text Score;
        private Text timeLeft;
        private int CurrentScore;
        private int CurrentLives;
        private Timer timer = new Timer();
        private Vec2F timerPosition = new Vec2F(0.8f, 0.8f);
        private Vec2F scorePosition = new Vec2F(0.2f, 0.8f);
        private int CurrenTime;
        private LivesCreator livesCreator = new LivesCreator(); 
        private EntityContainer<Entity> Lives = new EntityContainer<Entity>();
        public int GetTime {
            get {return CurrenTime;}
        }
        public int GetScore {
            get {return CurrentScore;}
        }
        public int GetLives {
            get {return CurrentLives;}
        }

        /// <summary>
        /// Sets an instance for the GameValues so only one is ever active
        /// </summary>
        /// <returns>The active GameValues</returns>
        public static GameValues GetInstance() {
            if (GameValues.instance == null) {
                GameValues.instance = new GameValues();
            }
            return GameValues.instance;
        }
        
        /// <summary>
        /// Creates different values displayed in game
        /// </summary>
        /// <param name="level">Current level</param>
        public void initializeNumber(string level) {
            CurrentScore = -1;
            CurrentLives = 0;
            UpdateScore();
            timeLeft = new Text(timer.StartTimer(level).ToString(),timerPosition,new Vec2F(0.2f, 0.2f));
            for (int i = 0; i < 3; i++){
                AddLives();
            }
            timeLeft.SetColor(System.Drawing.Color.DeepSkyBlue);
            timeLeft.SetFont("Comic Sans");
        }

        /// <summary>
        /// Updates the lives with the current Lives
        /// </summary>
        /// <param name="lives">current Lives</param>
        public void DecreaseLives() {
            CurrentLives--;
            livesCreator.Numbers(CurrentLives,Lives,new Vec2F(0.0f, 0.1f));
        }

        /// <summary>
        /// Updates the lives with the current Lives
        /// </summary>
        /// <param name="lives">current Lives</param>
        public void AddLives() {
            CurrentLives++;
            livesCreator.Numbers(CurrentLives,Lives,new Vec2F(0.0f, 0.1f));
        }

        /// <summary>
        /// Updates the time to the current time from timer.UpdateTime()
        /// </summary>
        public void UpdateTimer() {
            if (timer.UpdateTime() != CurrenTime) {
                CurrenTime = timer.UpdateTime();
                timeLeft = new Text(timer.GetTime.ToString(),timerPosition,new Vec2F(0.2f, 0.2f));
                timeLeft.SetColor(System.Drawing.Color.DeepSkyBlue);
                timeLeft.SetFont("Comic Sans");
            }
        }

        /// <summary>
        /// Updates the score to the current score
        /// </summary>
        /// <param name="CurrentScore">current score</param>
        public void UpdateScore() {
            CurrentScore++;
            Score = new Text(CurrentScore.ToString(),scorePosition,new Vec2F(0.2f, 0.2f));
            Score.SetColor(System.Drawing.Color.DeepSkyBlue);
            Score.SetFont("Comic Sans");
        }

        /// <summary>
        /// Renders the different values
        /// </summary>
        public void Render() {
            Score.RenderText();
            if (timer.GetTime > 0) {
                timeLeft.RenderText();
            }
            Lives.RenderEntities();
        }
    }
    
}