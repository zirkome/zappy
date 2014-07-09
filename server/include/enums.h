/*
** enums.h for enums in /home/sinet_l/Documents/project/zappy/server
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Jun 26 14:59:43 2014 luc sinet
** Last update Sat Jul  5 16:00:00 2014 luc sinet
*/

#ifndef _ENUMS_H_
# define _ENUMS_H_

typedef enum	bool
  {
    false = 0,
    true
  }		t_bool;

enum	e_command
  {
    FORWARD = 0,
    RIGHT = 1,
    LEFT = 2,
    SEE = 3,
    INVENTORY = 4,
    TAKE = 5,
    PUT = 6,
    EXPULSE = 7,
    BROADCAST = 8,
    INCANTATION = 9,
    FORK = 10,
    CONNECT_NBR = 11,
    MSZ = 12,
    BCT = 13,
    MCT = 14,
    TNA = 15,
    PPO = 16,
    PLV = 17,
    PIN = 18,
    SGT = 19,
    SST = 20
  };

enum	e_error
  {
    UNKNOWN_CMD = -1,
    BAD_PARAM = -2
  };

enum
  {
    PFOOD = 20,
    PLINEMATE = 30,
    PDERAUMERE = 25,
    PSIBUR = 30,
    PMENDIANE = 10,
    PPHIRAS = 15,
    PTHYSTAME = 5
  };

enum
  {
    PFIRST_CASE = 50,
    PSECOND_CASE = 30,
    PTHIRD_CASE = 20,
    PFOURTH_CASE = 10,
    PFIFTH_CASE = 5
  };

enum
  {
    FOOD = 1,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    PLAYER,
    EMPTY
  };

#endif /* _ENUMS_H_ */
