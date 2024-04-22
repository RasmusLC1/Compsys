using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using System.Diagnostics;
using Breakout.Gameinfo;

namespace Breakout.EntityData.PowerUps {
    public class InvinciblePowerup : PowerUp {
        Image img = new Image (Path.Combine("Assets", "Images", "InfinitePowerUp.png"));
        private GameValues values = GameValues.GetInstance();
        private int value;
        private int CurrentLives;
        Stopwatch stopwatch = new Stopwatch ();
        
        public InvinciblePowerup (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Image = img;
        }

        /// <summary>
        /// Starts a stopwatch and sets the value to 1 so that specialEffects can become active
        /// Teleports the powerup away so it is no longer visible on the board
        /// </summary>
        public override void Effect () {
            stopwatch.Start();
            value = 1;
            this.Shape.Position = new Vec2F(100f,500f);
            CurrentLives = values.GetLives;
        }

        /// <summary>
        /// Checks if player has lost lifes, if yes then it adds it back
        /// </summary>
        public override void SpecialEffect() {
            if (value == 1){
                if(CurrentLives > values.GetLives) {
                    values.AddLives();
                }
                if (stopwatch.Elapsed.Seconds  == 10) {
                    this.DeleteEntity();
                }
            }
        }
    }
}