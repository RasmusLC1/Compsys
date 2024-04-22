using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using Breakout.EntityData.EntityLogic;

namespace Breakout.Factories {
    public class PlayerFactory : IFactory {

        /// <summary>
        /// Handles PlayerCreation
        /// </summary>
        /// <param name="Position">Player Position</param>
        /// <returns> An entity </returns>
        public Entity Build(Vec2F Position) {
            Player player = new Player (
                new DynamicShape(Position, new Vec2F(0.16f, 0.03f)),
                new Image(Path.Combine("Assets", "Images", "Player.png"))); 
            return player;
        }
    }
}