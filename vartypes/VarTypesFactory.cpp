//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
#include "VarTypesFactory.h"
#include <assert.h>

namespace VarTypes {
  VarTypesFactory::VarTypesFactory()
  {
  }
  
  VarTypesFactory::~VarTypesFactory()
  {
  }
  
  VarPtr VarTypesFactory::newUserVarType(VarTypeId t) {
    (void)t;
    return VarPtr();
  }
  
  VarVal * VarTypesFactory::newUserVarVal(VarTypeId t) {
    (void)t;
    return 0;
  }
  
  VarTypeId VarTypesFactory::stringToUserType(const string & s) {
    (void)s;
    return VARTYPE_ID_UNDEFINED;
  }
  
  string VarTypesFactory::userTypeToString(VarTypeId t) {
    (void)t;
    return "undefined";
  } 
  
  VarPtr VarTypesFactory::newVarType(VarTypeId t) {
    if (t==VARTYPE_ID_BOOL) {
      return(VarPtr(new VarBool()));
    } else if (t==VARTYPE_ID_INT) {
        return(VarPtr(new VarInt()));
    } else if (t==VARTYPE_ID_SHORT) {
      return(VarPtr(new VarShort()));
    } else if (t==VARTYPE_ID_DOUBLE) {
      return(VarPtr(new VarDouble()));
    } else if (t==VARTYPE_ID_STRING) {
      return(VarPtr(new VarString()));
    } else if (t==VARTYPE_ID_BLOB) {
      return(VarPtr(new VarBlob()));
    } else if (t==VARTYPE_ID_EXTERNAL) {
      return(VarPtr(new VarExternal()));
    } else if (t==VARTYPE_ID_LIST) {
      return(VarPtr(new VarList()));
    } else if (t==VARTYPE_ID_STRINGENUM) {
      return(VarPtr(new VarStringEnum()));
    } else if (t==VARTYPE_ID_SELECTION) {
      return(VarPtr(new VarSelection()));
    } else if (t==VARTYPE_ID_QWIDGET) {
      return(VarPtr(new VarQWidget()));
    } else if (t==VARTYPE_ID_TRIGGER) {
      return(VarPtr(new VarTrigger()));
    } else {
      if (t >= VARTYPE_ID_MIN_USERTYPE) {
        VarPtr v = newUserVarType(t);
        if (v==0) {
          fprintf(stderr,"Error: failed to construct unknown user-defined VarType with VarTypeId: %d (type name: %s).\n",t,typeToString(t).c_str());
          fprintf(stderr,"Note, if you were trying to define your own VarType, you need to overload the newUserVarType(...) function from the VarTypesFactory class.\n");
        }
        return v;
      } else {
        fprintf(stderr,"Error: failed to construct unknown VarType with VarTypeId: %d (type name: %s).\n",t,typeToString(t).c_str());
        fprintf(stderr,"Note if you were trying to define your own VarType, you need to ensure ");
        fprintf(stderr,"that your VarTypeId is greater than %d, as all other values are reserved ",VARTYPE_ID_MIN_USERTYPE);
        fprintf(stderr,"for future native types.\n");
        fprintf(stderr,"Otherwise, this error could have been caused if you are trying to load a VarTypes file that was created with a newer version, containing types that were not yet implemented in this version.\n");
        return VarPtr();
      }
    }
  }
  
  VarVal * VarTypesFactory::newVarVal(VarTypeId t) {
    //TODO: add VarVal creation.
    (void)t;
    return 0;
  }

  VarTypeId VarTypesFactory::stringToType(const string & s) {
    if (s=="bool") {
      return VARTYPE_ID_BOOL;
    } else if (s=="double") {
      return VARTYPE_ID_DOUBLE;
    } else if (s=="int") {
      return VARTYPE_ID_INT;
    } else if (s=="string") {
      return VARTYPE_ID_STRING;
    } else if (s=="blob") {
      return VARTYPE_ID_BLOB;
    } else if (s=="external") {
      return VARTYPE_ID_EXTERNAL;
    } else if (s=="vector2d") {
      return VARTYPE_ID_VECTOR2D;
    } else if (s=="vector3d") {
      return VARTYPE_ID_VECTOR3D;
    } else if (s=="timeline") {
      return VARTYPE_ID_TIMELINE;
    } else if (s=="timevar") {
      return VARTYPE_ID_TIMEVAR;
    } else if (s=="list") {
      return VARTYPE_ID_LIST;
    } else if (s=="stringenum") {
      return VARTYPE_ID_STRINGENUM;
    } else if (s=="selection") {
      return VARTYPE_ID_SELECTION;
    } else if (s=="short") {
      return VARTYPE_ID_SHORT;
    } else if (s=="trigger") {
      return VARTYPE_ID_TRIGGER;
    } else if (s=="qwidget") {
      return VARTYPE_ID_QWIDGET;
    } else {
      VarTypeId v=stringToUserType(s);
      if (v==VARTYPE_ID_UNDEFINED) return v;
      if (v < VARTYPE_ID_MIN_USERTYPE) {
        fprintf(stderr,"Warning! stringToUserType needs to return a typeId greater or equal than %d (was %d for label '%s')\n",VARTYPE_ID_MIN_USERTYPE ,v, s.c_str());
        return VARTYPE_ID_UNDEFINED;
      } else {
        return v;
      }
    }
  }
  
  string VarTypesFactory::typeToString(VarTypeId vt)
  {
    if (vt==VARTYPE_ID_BOOL) {
      return "bool";
    } else if (vt==VARTYPE_ID_DOUBLE) {
      return "double";
    } else if (vt==VARTYPE_ID_INT) {
      return "int";
    } else if (vt==VARTYPE_ID_STRING) {
      return "string";
    } else if (vt==VARTYPE_ID_EXTERNAL) {
      return "external";
    } else if (vt==VARTYPE_ID_BLOB) {
      return "blob";
    } else if (vt==VARTYPE_ID_VECTOR2D) {
      return "vector2d";
    } else if (vt==VARTYPE_ID_VECTOR3D) {
      return "vector3d";
    } else if (vt==VARTYPE_ID_TIMEVAR) {
      return "timevar";
    } else if (vt==VARTYPE_ID_TIMELINE) {
      return "timeline";
    } else if (vt==VARTYPE_ID_LIST) {
        return "list";
      } else if (vt==VARTYPE_ID_STRINGENUM) {
        return "stringenum";
    } else if (vt==VARTYPE_ID_SELECTION) {
      return "selection";
    } else if (vt==VARTYPE_ID_SHORT) {
      return "short";
    } else if (vt==VARTYPE_ID_TRIGGER) {
      return "trigger";
    } else if (vt==VARTYPE_ID_QWIDGET) {
      return "qwidget";
    } else {
      string s = userTypeToString(vt);
      if (s=="" || s=="undefined") {
        printf("warning: unknown vartype: %d\n",vt);
        return "undefined";
      }
      return s;
    }
  }

  VarPtr VarTypesFactory::cloneVarType(VarPtr v)
  {
      switch (v->getType()) {
      ////    VARTYPE_ID_UNDEFINED=0,
      ////    VARTYPE_ID_BOOL,
      ////    VARTYPE_ID_INT,
      ////    VARTYPE_ID_DOUBLE,
      ////    VARTYPE_ID_STRING,
      ////    VARTYPE_ID_BLOB,
      ////    VARTYPE_ID_EXTERNAL,
      ////    VARTYPE_ID_VECTOR2D,
      ////    VARTYPE_ID_VECTOR3D,
      ////    VARTYPE_ID_TIMEVAR,
      ////    VARTYPE_ID_TIMELINE,
      ////    VARTYPE_ID_LIST,
      ////    VARTYPE_ID_STRINGENUM,
      ////    VARTYPE_ID_SELECTION,
      ////    VARTYPE_ID_SHORT,
      ////    VARTYPE_ID_TRIGGER,
      ////    VARTYPE_ID_QWIDGET,
      ////    VARTYPE_ID_COUNT,
      ////    VARTYPE_ID_MIN_USERTYPE=128
      case VARTYPE_ID_BOOL: {
          VarBool* bb = (VarBool*)(v.get());
          VarBool* _bool = new VarBool(bb->getName(), bb->getBool());
          return VarBoolPtr(_bool);
      }

      case VARTYPE_ID_INT: {
          VarInt* ii = (VarInt*)(v.get());
          VarInt* _int = new VarInt(ii->getName(), ii->getInt(), ii->getMin(), ii->getMax());
          return VarIntPtr(_int);
      }

      case VARTYPE_ID_DOUBLE: {
          VarDouble* dd = (VarDouble*)(v.get());
          VarDouble* _double = new VarDouble(dd->getName(), dd->getDouble(), dd->getMin(), dd->getMax());
          return VarDoublePtr(_double);
      }

      case VARTYPE_ID_STRING: {
          VarString* ss = (VarString*)(v.get());
          VarString* _string = new VarString(ss->getName(), ss->getString());
          return VarStringPtr(_string);
      }

      case VARTYPE_ID_LIST: {
          VarList* ss = (VarList*)(v.get());
          VarList* _list = new VarList(ss->getName());
          for(int i=0; i<ss->getChildrenCount(); i++) {
              _list->addChild(cloneVarType(ss->getChildren()[i]));
          }
          return VarListPtr(_list);
      }

      case VARTYPE_ID_SELECTION: {
          VarSelection* ss = (VarSelection*)(v.get());
          VarSelection* _selection = new VarSelection(ss->getName(), ss->getCount());
          for(uint i=0; i<ss->getCount(); i++) {
              // _selection->addItem(false, ss->getChildren());
          }
          return VarSelectionPtr(_selection);
      }

      case VARTYPE_ID_SHORT: {
          VarShort* ss = (VarShort*)(v.get());
          VarShort* _short = new VarShort(ss->getName(), ss->getShort(), ss->getMin(), ss->getMax());
          return VarShortPtr(_short);
      }

      default:
          return NULL;
      }
  }

  void VarTypesFactory::copyVarType(VarPtr src, VarPtr dst)
  {
      assert(src->getType() == dst->getType());
      switch (src->getType()) {
      ////    VARTYPE_ID_UNDEFINED=0,
      ////    VARTYPE_ID_BOOL,
      ////    VARTYPE_ID_INT,
      ////    VARTYPE_ID_DOUBLE,
      ////    VARTYPE_ID_STRING,
      ////    VARTYPE_ID_BLOB,
      ////    VARTYPE_ID_EXTERNAL,
      ////    VARTYPE_ID_VECTOR2D,
      ////    VARTYPE_ID_VECTOR3D,
      ////    VARTYPE_ID_TIMEVAR,
      ////    VARTYPE_ID_TIMELINE,
      ////    VARTYPE_ID_LIST,
      ////    VARTYPE_ID_STRINGENUM,
      ////    VARTYPE_ID_SELECTION,
      ////    VARTYPE_ID_SHORT,
      ////    VARTYPE_ID_TRIGGER,
      ////    VARTYPE_ID_QWIDGET,
      ////    VARTYPE_ID_COUNT,
      ////    VARTYPE_ID_MIN_USERTYPE=128
      case VARTYPE_ID_BOOL: {
          VarBool* _src = (VarBool*)(src.get());
          VarBool* _dst = (VarBool*)(dst.get());
          _dst->setName(_src->getName());
          _dst->setBool(_src->getBool());
      }

      case VARTYPE_ID_INT: {
          VarInt* _src = (VarInt*)(src.get());
          VarInt* _dst = (VarInt*)(dst.get());
          _dst->setName(_src->getName());
          _dst->setInt(_src->getInt());
      }

      case VARTYPE_ID_DOUBLE: {
          VarDouble* _src = (VarDouble*)(src.get());
          VarDouble* _dst = (VarDouble*)(dst.get());
          _dst->setName(_src->getName());
          _dst->setDouble(_src->getDouble());
      }

      case VARTYPE_ID_STRING: {
          VarString* _src = (VarString*)(src.get());
          VarString* _dst = (VarString*)(dst.get());
          _dst->setName(_src->getName());
          _dst->setString(_src->getString());
      }

      case VARTYPE_ID_LIST: {
          VarList* _src = (VarList*)(src.get());
          VarList* _dst = (VarList*)(dst.get());
          _dst->setName(_src->getName());

          for(int i=0; i<_src->getChildrenCount(); i++) {
              copyVarType(_src->getChildren()[i], _dst->getChildren()[i]);
          }
      }

      case VARTYPE_ID_SELECTION: {

      }

      case VARTYPE_ID_SHORT: {
          VarShort* _src = (VarShort*)(src.get());
          VarShort* _dst = (VarShort*)(dst.get());
          _dst->setName(_src->getName());
          _dst->setShort(_src->getShort());
      }

      default:
          return ;
      }

  }
};
