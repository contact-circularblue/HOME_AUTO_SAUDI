bool connect_socket()
{
  while (socket_connected != true)
    client.monitor();
  return true;
}
