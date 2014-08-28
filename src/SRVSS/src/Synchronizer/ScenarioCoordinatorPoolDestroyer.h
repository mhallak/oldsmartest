#ifndef SCENARIOCOORDINATORPOOLDESTROYER_H_
#define SCENARIOCOORDINATORPOOLDESTROYER_H_

class ScenarioCoordinatorPool;
class ScenarioCoordinatorPoolDestroyer {
		public:
		ScenarioCoordinatorPoolDestroyer(){}
			ScenarioCoordinatorPoolDestroyer(ScenarioCoordinatorPool *d)
			{
					_doomed = d;
			}

			~ScenarioCoordinatorPoolDestroyer();

			void SetDoomed(ScenarioCoordinatorPool *d)
			{
				_doomed = d;
			}

		private:
			// Prevent users from making copies of a
			// Destroyer to avoid double deletion:
			ScenarioCoordinatorPoolDestroyer(const ScenarioCoordinatorPoolDestroyer &);
			void operator = (const ScenarioCoordinatorPoolDestroyer &);
			private: ScenarioCoordinatorPool *_doomed;
};
#endif
