# Fan Controller
An embedded system project that simulates a fan controller on proutes using a 3-layer modular architecture. 

# Workflow
The system will adjust the fan speed based on a temperature read from a sensor. It will be adjusted as follows : 
* temperature
  * **less than 30** : The fan is off. 
  * **greater than or equal to 30** : the fan work wiht 25% of it's maximum speed.
  * **greater than or equal to 60** : the fan work wiht 50% of it's maximum speed.
  * **greater than or equal to 90** : the fan work wiht 75% of it's maximum speed.
  * **greater than or equal to 120** : the fan work wiht 100% of it's maximum speed.

# Architecture & Modules

  
