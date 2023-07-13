import { inject } from '@angular/core';
import { CanActivateFn, Router } from '@angular/router';
import { DataService } from '../services/data.service';

export const authGuard: CanActivateFn = (route, state) => {
  const dataService = inject(DataService);
  const router = inject(Router);

  if (dataService._isLoggedIn.value) {
    return true;
  }

  dataService._errorToastMessage.next("Sie müssen eingeloggt sein, um auf Ihr Portfolio zugreifen zu können.");
  return router.parseUrl("/stocks");
};
