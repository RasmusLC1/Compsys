using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using Breakout.EntityData.EntityLogic;

namespace Breakout.Factories {
    public class BallFactory : IFactory {
        
        /// <summary>
        /// Handles BallCreation
        /// </summary>
        /// <param name="Position">Ball Position</param>
        /// <returns></returns>
        public Entity Build (Vec2F Position) {
            Ball ball = new Ball (
                new DynamicShape(Position, new Vec2F(0.05f, 0.05f)),
                new Image(Path.Combine("Assets", "Images", "Ball.png")));
            return ball;
        }
    }
}