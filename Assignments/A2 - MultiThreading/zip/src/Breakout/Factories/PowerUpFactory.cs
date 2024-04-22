using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using System;
using System.Collections.Generic;
using Breakout.EntityData.Blocks;
using Breakout.EntityData.PowerUps;

namespace Breakout.Levels { 
    public class PowerUpFactory {
        private Random rand = new Random ();

        /// <summary>
        /// Creates the PowerUps on the position of the BlockType
        /// </summary>
        /// <param name="block">PowerUpBlock</param>
        public EntityContainer <PowerUp> PowerUpBuilder(Block block, EntityContainer <PowerUp> powerUps, List<string> powerups) {
            int index = rand.Next(powerups.Count);
            Type PowerUptype = Type.GetType("Breakout.EntityData.PowerUps." + powerups[index]);
            PowerUp powerUp = (PowerUp)Activator.CreateInstance(PowerUptype,
                new DynamicShape(new Vec2F(block.Shape.Position.X, block.Shape.Position.Y), new Vec2F(0.05f, 0.05f)),
                new Image(Path.Combine("Assets", "Images", "WallPowerUp.png")));
            powerUps.AddEntity(powerUp);
            return powerUps;
        }
    }
}