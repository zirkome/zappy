/*
** enums.h for enums in /home/sinet_l/Documents/project/zappy/server
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Jun 26 14:59:43 2014 luc sinet
** Last update Fri Jul  4 15:31:07 2014 luc sinet
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
    FORWARD = 1,
    RIGHT = 2,
    LEFT = 3,
    SEE = 4,
    INVENTORY = 5,
    TAKE = 6,
    PUT = 7,
    EXPULSE = 8,
    BROADCAST = 9,
    INCANTATION = 10,
    FORK = 11,
    CONNECT_NBR = 12,
    MSZ = 13,
    BCT = 14,
    MCT = 15,
    TNA = 16,
    PPO = 17,
    PLV = 18,
    PIN = 19,
    SGT = 20,
    SST = 21
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
