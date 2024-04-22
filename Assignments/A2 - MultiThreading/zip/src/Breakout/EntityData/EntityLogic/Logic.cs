using DIKUArcade.Entities;
using Breakout.EntityData.Blocks;
using Breakout.EntityData.PowerUps;

namespace Breakout.EntityData.EntityLogic {
    public class Logic {
        private BallHitDetection ballHitDetection = new BallHitDetection();
        private PowerUpHitDetection powerupHitDetection = new PowerUpHitDetection();

        /// <summary>
        /// Gathers the logic for powerup and ball in one function. Only triggers PowerUpLogic when there
        /// is an active PowerUp
        /// </summary>
        /// <param name="blocks">Blocks currently loaded</param>
        /// <returns>int for Moveball logic</returns>
        public void EntityLogic (EntityContainer<Block> blocks, EntityContainer<Ball> balls,
        EntityContainer<PowerUp> powerUps, Player player) {
            player.Move();
            ballHitDetection.HitDetection(balls,blocks, powerUps, player);
            powerUps.Iterate(powerUp => {
                if (powerUp.IsActive) {
                    powerUp.SpecialEffect();
                    powerupHitDetection.HitDetection(powerUp, player);
                }
            }); 
        }
    }
}