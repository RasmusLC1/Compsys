using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using Breakout.BreakoutStates;
using Breakout.Factories;
using Breakout.EntityData.EntityLogic;

namespace Breakout.EntityData.PowerUps {
    public class ExtraBallPowerup : PowerUp {
        Image img = new Image (Path.Combine("Assets", "Images", "ExtraBallPowerUp.png"));
        private GameRunning gameRunning = GameRunning.GetInstance();
        private CentralFactory factory= new CentralFactory();
        
        public ExtraBallPowerup (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Image = img;
        }

        /// <summary>
        /// Creates an extra ball and deletes the powerup
        /// </summary>
        public override void Effect () {
            gameRunning.AddBalls((Ball)(factory.Build(new Vec2F(gameRunning.GetPlayer.Shape.Position.X,
            gameRunning.GetPlayer.Shape.Position.Y+0.05f), "Ball")));
            this.DeleteEntity();
        }
        
        public override void SpecialEffect () {}
    }
}