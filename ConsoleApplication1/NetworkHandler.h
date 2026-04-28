#ifndef __NetworkHandler__
#define __NetworkHandler__

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>
#include <memory>
#include <vector>

namespace whytsoft
{

	class NetworkHandler
	{
	private:
		static const size_t READ_DATA_BUFSIZE = 1024;
		static const size_t WRITE_DATA_BUFSIZE = 8192 * 3;

		struct CallbackBase
		{
			virtual ~CallbackBase() {}
			virtual void Call(size_t _id) = 0;
		};

		template <class F>
		struct Callback : public CallbackBase
		{
			Callback(F _f) : m_f(_f) {}

			virtual void Call(size_t _id)
			{
				m_f(_id);
			}

			F m_f;
		};

		struct SOCKET_INFORMATION {
			SOCKET_INFORMATION(SOCKET _s, CallbackBase* _connectionClosedCallback) : writeLen(0), Socket(_s), BytesRECV(0), m_connectionClosedCallback(_connectionClosedCallback) {}
			char readBuffer[READ_DATA_BUFSIZE]{};
			char writeBuffer[WRITE_DATA_BUFSIZE]{};
			int writeLen;
			SOCKET Socket;
			DWORD BytesRECV;
			CallbackBase* m_connectionClosedCallback;
		};

		enum { USERS_LISTENER, REMOTE_SERVER_LISTENER, NUM_LISTENERS };

		static void InitWsa();
		static void InitListener(SOCKET* _socket, unsigned short _port);

	public:
		NetworkHandler(unsigned short _usersPort)
			: m_usersPort(_usersPort)
			, m_remoteServerPort(0)
			, m_numListeners(1)
			, m_totalSockets(0)
			, m_nextReadSocketToTraverse(0), m_totalSocketsReady(0)
		{
			m_newConnectionFunc[USERS_LISTENER].reset(new Callback<OnNewConnection>(OnNewConnection{ *this }));
			m_closedConnectionFunc[USERS_LISTENER].reset(new Callback<OnConnectionClosed>(OnConnectionClosed{ *this }));

			Init();
			FD_ZERO(&m_lastReadSet);
		}

		virtual ~NetworkHandler() = default;
		NetworkHandler(const NetworkHandler&) = delete;
		NetworkHandler& operator=(const NetworkHandler&) = delete;

		void GetInput(size_t* _socketid, std::string* _input);
		void PutOutput(size_t _socketid, const std::string& _output);

	private:
		virtual void onNewConnection(size_t socketId) const = 0;
		virtual void onConnectionClosed(size_t socketId) const = 0;

		struct OnNewConnection
		{
			OnNewConnection(NetworkHandler& _nh) : nh(_nh) {}
			void operator()(size_t userId) { nh.onNewConnection(userId); };
			NetworkHandler& nh;
		};

		struct OnConnectionClosed
		{
			OnConnectionClosed(NetworkHandler& _nh) : nh(_nh) {}
			void operator()(size_t userId) { nh.onConnectionClosed(userId); };
			NetworkHandler& nh;
		};

		void Init();
		size_t CreateSocketInformation(SOCKET s, size_t _listenerIdx);
		void FreeSocketInformation(DWORD Index);

		unsigned short m_usersPort;
		unsigned short m_remoteServerPort;
		size_t m_numListeners;
		DWORD m_totalSockets;

		// from here they are initialized by Init()
		std::unique_ptr<CallbackBase> m_newConnectionFunc[NUM_LISTENERS];
		std::unique_ptr<CallbackBase> m_closedConnectionFunc[NUM_LISTENERS];
		SOCKET m_listenSocket[NUM_LISTENERS];
		SOCKET_INFORMATION* m_socketArray[FD_SETSIZE];
		FD_SET m_lastReadSet;
		int m_nextReadSocketToTraverse;
		size_t m_totalSocketsReady;
		std::vector<size_t> m_virtualSocketIdToRealSocketId;
	};

} // whytsoft

#endif
