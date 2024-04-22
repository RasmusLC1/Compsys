using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;

namespace Breakout.Factories {
    public class LivesFactory : IFactory {

        /// <summary>
        /// Handles PlayerCreation
        /// </summary>
        /// <param name="Position">Player Position</param>
        /// <returns></returns>
        public Entity Build(Vec2F Position) {
            Entity Lives = new Entity (
                new DynamicShape(Position, new Vec2F(0.05f, 0.05f)),
                new Image(Path.Combine("Assets", "Images", "LifePickUp.png"))); 
            return Lives;
        }
    }
}