using DIKUArcade.Events;

namespace Breakout {
    public static class BreakoutBus {
        private static GameEventBus eventBus;
        public static GameEventBus GetEventBus {
            get {return eventBus;}
        }

        /// <summary>
        /// Creates a GameEventBus if null, ortherwise returns the already instanciated GameEventBus
        /// </summary>
        /// <returns>A GameEventBus</returns>
        public static GameEventBus GetBus() {
            if (eventBus == null) {
                eventBus = new GameEventBus();
            }
            return eventBus;
        }
    }
}