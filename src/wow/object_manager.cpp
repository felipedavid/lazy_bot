
namespace WoW {

	struct TSGrowableArray {
	};

	struct TSLink {
		TSLink *Prev;
		TSLink *Next;
	};

	struct TSList {
		u32 object_size;
		u32 unknown;
		TSLink Link;
	};

	struct TSHashTable {
		void *vtable;
		TSList List;
	};

	struct CGObjectManager {
		TSHashTable AtiveObjects;
	};

	CGObjectManager *s_curMgr;

}