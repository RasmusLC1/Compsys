using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using Breakout.BreakoutStates;
using System.Diagnostics;
using Breakout.EntityData.EntityLogic;

namespace Breakout.EntityData.PowerUps {
    public class DoubleSizePowerUp : PowerUp {
        Image img = new Image (Path.Combine("Assets", "Images", "BigPowerUp.png"));
        private GameRunning gameRunning = GameRunning.GetInstance();
        private int value;
        Stopwatch stopwatch = new Stopwatch ();
        
        public DoubleSizePowerUp (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Image = img;
        }

        /// <summary>
        /// Starts a stopwatch and changes the balls extent and sets the value to 1 so that specialEffects can become active
        /// Teleports the powerup away so it is no longer visible on the board
        /// </summary>
        public override void Effect () {
            stopwatch.Start();
            value = 1;
            this.Shape.Position = new Vec2F(100f,500f);
            foreach (Ball ball in gameRunning.GetBalls) {
                ball.Shape.Extent = new Vec2F(0.10f, 0.10f);
            }      
        }

        /// <summary>
        /// Changes the ball back when time has run out and deletes the powerUp
        /// </summary>
        public override void SpecialEffect () {
            if (value == 1) {
                if (stopwatch.Elapsed.Seconds == 6) {
                    foreach (Ball ball in gameRunning.GetBalls) {
                        ball.Shape.Extent = new Vec2F(0.05f, 0.05f);
                    }
                    this.DeleteEntity();
                }
            }
        }
    }
}